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
#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    int sock_fd;
    char sendline[BUFFER_SIZE];
    char recvline[BUFFER_SIZE];

    struct sockaddr_in server_address;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_fd, (const struct sockaddr *) &server_address, sizeof server_address) < 0)
        goto error_out;

    while (fgets(sendline, BUFFER_SIZE, stdin) != NULL) {
        ssize_t send_len, recv_len = 0;

        if((send_len = send(sock_fd, sendline, strlen(sendline), 0)) < 0)
            goto error_out;

        // SOCK_STREAM: connection-oriented byte streams
        // 因为无法保证一次读取正好能拿到服务端一次写入的所有字节
        // 所以这里需要判断接收字符的长度是否等于发送字节的长度
        // 对于一些无法预知读取字节长度的应用，需要自己定义合理的应用层协议
        while (recv_len < send_len) {
            bzero(recvline, BUFFER_SIZE);
            ssize_t recv_count;
            if ((recv_count = recv(sock_fd, recvline, BUFFER_SIZE, 0)) < 0)
                goto error_out;
            recv_len += recv_count;
        }

        fputs(recvline, stdout);
    }

    error_out:
    close(sock_fd);
    return -1;
}
