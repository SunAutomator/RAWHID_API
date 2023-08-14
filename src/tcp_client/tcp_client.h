#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <stdbool.h>

typedef struct {
    char *host;
    int port;
} tcp_client_connection_info_t;

typedef struct {
    char *host;
    int port;
    int socket_fd;
} TCPClient;

bool tcp_client_connect(TCPClient *client, const char *host, int port);
bool tcp_client_send(TCPClient *client, const unsigned char *data, size_t size);
int tcp_client_receive(TCPClient *client, unsigned char *buffer, size_t size);
void tcp_client_disconnect(TCPClient *client);

#endif // TCP_CLIENT_H
