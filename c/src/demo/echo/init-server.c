//
// Created by xy on 19-1-6.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define QUEUE_LENGTH 10

int init_server(int type, uint16_t port) {
    int listen_fd;

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create listen socket failed");
        return -1;
    }

    if (bind(listen_fd, (struct sockaddr *) &server_address, sizeof server_address) < 0) {
        perror("bind failed");
        goto error_out;
    }

    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(listen_fd, QUEUE_LENGTH) < 0) {
            perror("listen failed");
            goto error_out;
        }
    }

    printf("server is listening on port: %d\n", (int)port);

    return listen_fd;

    error_out:
    close(listen_fd);
    return -1;
}