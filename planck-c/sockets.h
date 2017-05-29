#include <stdbool.h>

typedef void *(*connection_handler_t)(void *socket_desc);

typedef void (*listen_successful_cb_t)(void);

typedef struct accepted_connection_cb_return {
    int err;
    void* state;
} accepted_connection_cb_return_t;

typedef accepted_connection_cb_return_t* (*accepted_connection_cb_t)(int sock, void* state);

typedef struct connection_data_arrived_return {
    int err;
    bool close;
} connection_data_arrived_return_t;

typedef connection_data_arrived_return_t* (*connection_data_arrived_cb_t)(char* data, int sock, void* state);

typedef struct socket_accept_data {
    char *host;
    int port;
    listen_successful_cb_t listen_successful_cb;
    accepted_connection_cb_t accepted_connection_cb;
    connection_data_arrived_cb_t connection_data_arrived_cb;
    void* state;
} socket_accept_data_t;

int write_to_socket(int fd, const char *text);

void *accept_connections(void *data);

int close_socket(int fd);
