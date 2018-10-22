//
// Created by xy on 18-11-21.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 22000
#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    int sock_fd;
    char recvline[BUFFER_SIZE];

    struct sockaddr_in server_address;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock_fd, (const struct sockaddr *) &server_address, sizeof server_address) < 0)
        goto error_out;

    if (recv(sock_fd, recvline, BUFFER_SIZE, 0) <= 0)
        goto error_out;

    fputs(recvline, stdout);

    error_out:
    close(sock_fd);
    return -1;
}
