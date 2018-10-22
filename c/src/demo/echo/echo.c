//
// Created by xy on 19-1-6.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 4096

int echo(int sock_fd) {
    ssize_t length;
    struct sockaddr client_address;
    socklen_t addr_len = sizeof client_address;

    char buffer[MAXLINE];
    memset(buffer, 0, MAXLINE);

    if ((length = recvfrom(sock_fd, buffer, MAXLINE, 0, &client_address, &addr_len)) < 0) {
        perror("receive error");
        return -1;
    }

    if (length > 0) {
        printf("String received from and resent to the client:%s", buffer);
    }

    if ((sendto(sock_fd, buffer, (size_t) length, 0, &client_address, addr_len)) < 0) {
        perror("send error");
        return -1;
    }

    return (int) length;
}