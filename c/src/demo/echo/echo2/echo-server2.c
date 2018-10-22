//
// Single process user datagram based echo server
// Created by xy on 18-10-18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../echo.h"

#define PORT 22000

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return -1;

    if (bind(sock_fd, (struct sockaddr *) &server_address, sizeof server_address) < 0)
        goto error_out;

    while (echo(sock_fd) > 0);

    close(sock_fd);
    return 0;

    error_out:
    close(sock_fd);
    return -1;
}

