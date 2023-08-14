#include "tcp_client.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

bool tcp_client_connect(TCPClient *client, const char *host, int port) {
    struct addrinfo hints, *res, *p;
    int status;
    char port_str[16];

    snprintf(port_str, sizeof(port_str), "%d", port);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(host, port_str, &hints, &res)) != 0) {
        return false;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        if ((client->socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }

        if (connect(client->socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(client->socket_fd);
            continue;
        }

        break;
    }

    freeaddrinfo(res);
    return p != NULL;
}

bool tcp_client_send(TCPClient *client, const unsigned char *data, size_t size) {
    return send(client->socket_fd, data, size, 0) == size;
}

int tcp_client_receive(TCPClient *client, unsigned char *buffer, size_t size) {
    return recv(client->socket_fd, buffer, size, 0);
}

void tcp_client_disconnect(TCPClient *client) {
    close(client->socket_fd);
    client->socket_fd = -1;
}
