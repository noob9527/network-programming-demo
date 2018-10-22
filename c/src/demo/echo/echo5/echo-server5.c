//
// echo server based on select function
// Created by xy on 18-10-18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

#include "../init-server.h"
#include "../echo.h"

#define PORT 22000
#define MAX_CLIENTS 30


int main(int argc, char *argv[]) {
    int listen_fd, connection_fd;
    struct sockaddr client_address;
    socklen_t client_addr_len = sizeof client_address;

    if ((listen_fd = init_server(SOCK_STREAM, PORT)) < 0)
        return -1;

    fd_set readfds;
    int client_sockets[MAX_CLIENTS];
    int maxfd;

    // initialize all client_sockets to 0
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        client_sockets[i] = 0;
    }

    while (1) {
        FD_ZERO(&readfds);
        maxfd = listen_fd;
        FD_SET(maxfd, &readfds);

        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (!client_sockets[i]) continue;
            if (client_sockets[i] > maxfd) maxfd = client_sockets[i];
            FD_SET(client_sockets[i], &readfds);
        }

        int activity_count = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (activity_count < 0) {
            perror("select error");
            goto error_out;
        }

        // listen_fd is ready
        if (FD_ISSET(listen_fd, &readfds)) {
            if ((connection_fd = accept(listen_fd, &client_address, &client_addr_len)) < 0)
                goto error_out;

            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (client_sockets[i]) continue;
                client_sockets[i] = connection_fd;
                break;
            }
        }

        // check if other fd is ready
        for (int j = 0; j < MAX_CLIENTS; ++j) {
            int sd = client_sockets[j];

            if (!FD_ISSET(sd, &readfds)) continue;

            if (echo(sd) == 0) {
                // disconnect
                close(sd);
                client_sockets[j] = 0;
            }
        }
    }

    error_out:
    close(listen_fd);
    return -1;
}

