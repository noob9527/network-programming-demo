//
// Multiple threads stream based echo server
// Created by xy on 18-10-18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include "../init-server.h"
#include "../echo.h"

#define PORT 22000

void *thr_fn(void *arg) {
    int connection_fd = *(int *) arg;
    pthread_t tid = pthread_self();
    printf("thread id: %lu (0x%lx)\n", (unsigned long) tid, (unsigned long) tid);

    while (echo(connection_fd) > 0);
    close(connection_fd);

    return (void *) 0;
}

int main(int argc, char *argv[]) {
    int listen_fd, connection_fd;
    struct sockaddr client_address;
    socklen_t client_addr_len = sizeof client_address;

    if ((listen_fd = init_server(SOCK_STREAM, PORT)) < 0)
        return -1;

    while (1) {
        if ((connection_fd = accept(listen_fd, &client_address, &client_addr_len)) < 0)
            goto error_out;

        pthread_t ntid;

        int err;
        if ((err = pthread_create(&ntid, NULL, thr_fn, &connection_fd)) < 0) {
            char *msg = strerror(err);
            fputs(msg, stderr);
            goto error_out;
        }
    }

    error_out:
    close(listen_fd);
    return -1;
}

