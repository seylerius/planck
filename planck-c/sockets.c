#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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
        accepted_connection_cb_return = connection_handler_data->socket_accept_data->accepted_connection_cb(connection_handler_data->sock);
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

void *accept_connections(void *data) {

    socket_accept_data_t* socket_accept_data = (socket_accept_data_t*)data;

    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        engine_perror("Could not create listen socket");
        return NULL;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(socket_accept_data->port);

    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        engine_perror("Socket bind failed");
        return NULL;
    }

    listen(socket_desc, 3);

    if (socket_accept_data->listen_successful_cb) {
        socket_accept_data->listen_successful_cb();
    }

    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {

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
