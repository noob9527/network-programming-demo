//
// Single process stream based echo server
// Created by xy on 18-10-18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

#include "share.h"
#include "../init-server.h"
#include "../echo.h"

#define PORT 22000

int main(int argc, char *argv[]) {
    int listen_fd, connection_fd;
    struct sockaddr client_address;
    socklen_t client_addr_len = sizeof client_address;

    if ((listen_fd = init_server(SOCK_STREAM, PORT)) < 0)
        return -1;

    while (1) {
        if ((connection_fd = accept(listen_fd, &client_address, &client_addr_len)) < 0)
            goto error_out;

        printf("Received request...\n");

        char address_str[INET6_ADDRSTRLEN];
        get_address_str(client_address, address_str, INET6_ADDRSTRLEN);

        printf("address: %s\n", address_str);
        printf("port: %d\n", get_port(client_address));

        while (echo(connection_fd) > 0);

        close(connection_fd);
    }

    error_out:
    close(listen_fd);
    return -1;
}

