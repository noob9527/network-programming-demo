//
// Created by xy on 18-11-21.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define message "helloworld"
#define QUEUE_LENGTH 10
#define PORT 22000

int main(int argc, char *argv[]) {
    int listen_fd;
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    if (bind(listen_fd, (struct sockaddr *) &server_address, sizeof server_address) < 0)
        goto error_out;

    if (listen(listen_fd, QUEUE_LENGTH) < 0)
        goto error_out;

    while (1) {
        int connection_fd;
        if ((connection_fd = accept(listen_fd, NULL, NULL)) < 0)
            goto error_out;

        printf("Received request...\n");

        send(connection_fd, message, sizeof(message), 0);

        close(connection_fd);
    }

    error_out:
    close(listen_fd);
    return -1;
}