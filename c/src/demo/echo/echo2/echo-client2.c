//
// Created by xy on 18-10-18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define SERVER_PORT 22000
#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    int sock_fd;
    char sendline[BUFFER_SIZE];
    char recvline[BUFFER_SIZE];

    struct sockaddr_in server_address;

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return -1;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(SERVER_PORT);

    while (fgets(sendline, BUFFER_SIZE, stdin) != NULL) {
        if(sendto(sock_fd, sendline, strlen(sendline), 0, (const struct sockaddr *) &server_address, sizeof server_address) < 0)
            goto error_out;

        bzero(recvline, BUFFER_SIZE);
        if (recv(sock_fd, recvline, BUFFER_SIZE, 0) < 0)
            goto error_out;

        fputs(recvline, stdout);
    }

    error_out:
    close(sock_fd);
    return -1;
}
