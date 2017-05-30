#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "sockets.h"
#include "engine.h"

int write_to_socket(int fd, const char *text) {

    while (true) {

        fd_set fds;
        FD_ZERO(&fds);

        FD_SET(fd, &fds);

        int rv = select(fd + 1, NULL, &fds, NULL, NULL);

        if (rv == -1) {
            if (errno == EINTR) {
                // We ignore interrupts and loop back around
            } else {
                return -1;
            }
        } else {
            size_t len = strlen(text);
            ssize_t n = write(fd, text, len);
            if (n == len) {
                return 0;
            }
            if (n == -1) {
                return -1;
            }
            text += n;
        }
    }
}

typedef struct connection_handler_data {
    int sock;
    socket_accept_data_t* socket_accept_data;
} connection_handler_data_t;

void *connection_handler(void *data) {

    connection_handler_data_t* connection_handler_data = (connection_handler_data_t*)data;

    accepted_connection_cb_return_t* accepted_connection_cb_return = NULL;
    if (connection_handler_data->socket_accept_data->accepted_connection_cb) {
        accepted_connection_cb_return = connection_handler_data->socket_accept_data->accepted_connection_cb(
                connection_handler_data->sock, connection_handler_data->socket_accept_data->state);
    }

    int err = 0;
    void* state = NULL;
    if (accepted_connection_cb_return) {
        err = accepted_connection_cb_return->err;
        state = accepted_connection_cb_return->state;
        free(accepted_connection_cb_return);
    }

    ssize_t read_size;
    char receive_buffer[4096];

    connection_data_arrived_return_t* connection_data_arrived_return = NULL;

    while (!err && (read_size = recv(connection_handler_data->sock, receive_buffer, 4095, 0)) > 0) {
        receive_buffer[read_size] = '\0';
        connection_data_arrived_return = connection_handler_data->socket_accept_data->connection_data_arrived_cb(
                receive_buffer, connection_handler_data->sock, state);

        err = connection_data_arrived_return->err;
        bool close_socket = connection_data_arrived_return->close;
        free(connection_data_arrived_return);

        if (close_socket) {
            close(connection_handler_data->sock);
            break;
        }
    }

    free(data);

    return NULL;
}

int bind_and_listen(socket_accept_data_t* socket_accept_data) {

    struct sockaddr_in server;

    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        return socket_desc;
    }
    socket_accept_data->socket_desc = socket_desc;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(socket_accept_data->port);

    int err = bind(socket_desc, (struct sockaddr *) &server, sizeof(server));
    if (err == -1) {
        return err;
    }

    return listen(socket_desc, 3);
}

void *accept_connections(void *data) {

    socket_accept_data_t* socket_accept_data = (socket_accept_data_t*)data;

    if (socket_accept_data->listen_successful_cb) {
        socket_accept_data->listen_successful_cb();
    }

    int c = sizeof(struct sockaddr_in);
    int new_socket;
    struct sockaddr_in client;
    while ((new_socket = accept(socket_accept_data->socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {

        pthread_t handler_thread;

        connection_handler_data_t* connection_handler_data = malloc(sizeof(connection_handler_data_t));
        connection_handler_data->sock = new_socket;
        connection_handler_data->socket_accept_data = socket_accept_data;

        if (pthread_create(&handler_thread, NULL, connection_handler, connection_handler_data) < 0) {
            engine_perror("could not create thread");
            return NULL;
        }
    }

    if (new_socket < 0) {
        engine_perror("accept failed");
        return NULL;
    }

    return NULL;
}

int close_socket(int fd) {
    return shutdown(fd, SHUT_RDWR);
}

typedef struct read_inbound_socket_info {
    int socket_desc;
    connection_data_arrived_cb_t connection_data_arrived_cb;
    void* data_arrived_state;
} read_inbound_socket_info_t;

void* read_inbound_socket_data(void *data) {

    read_inbound_socket_info_t* read_inbound_socket_info = data;

    ssize_t read_size;
    char receive_buffer[4096];

    while ((read_size = recv(read_inbound_socket_info->socket_desc, receive_buffer, 4095, 0)) > 0) {
        receive_buffer[read_size] = '\0';
        connection_data_arrived_return_t* connection_data_arrived_return =read_inbound_socket_info->connection_data_arrived_cb(
                receive_buffer, read_inbound_socket_info->socket_desc, read_inbound_socket_info->data_arrived_state);
        free(connection_data_arrived_return);
    }

    free(read_inbound_socket_info);

    return NULL;
}

int open_socket(const char *host, int port, connection_data_arrived_cb_t connection_data_arrived_cb, void* data_arrived_state) {

    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        return socket_desc;
    }

    struct hostent *server = gethostbyname(host);
    if (server == NULL) {
        // no such host
        return -1;
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);

    int err = connect(socket_desc, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (err == -1) {
        return err;
    } else {
        read_inbound_socket_info_t* read_inbound_socket_info = malloc(sizeof(read_inbound_socket_info_t));
        read_inbound_socket_info->socket_desc = socket_desc;
        read_inbound_socket_info->connection_data_arrived_cb = connection_data_arrived_cb;
        read_inbound_socket_info->data_arrived_state = data_arrived_state;

        pthread_t reader_thread;

        if (pthread_create(&reader_thread, NULL, read_inbound_socket_data, read_inbound_socket_info) < 0) {
            engine_perror("could not create thread");
            return -1;
        }
        return socket_desc;
    }
}
