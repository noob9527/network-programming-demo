//
// echo server based on epoll function
// reference:
// https://medium.com/@copyconstruct/the-method-to-epolls-madness-d9d2d6378642
// https://idea.popcount.org/2017-02-20-epoll-is-fundamentally-broken-12/
// https://idea.popcount.org/2017-03-20-epoll-is-fundamentally-broken-22/
//
// Created by xy on 18-10-18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "../init-server.h"
#include "../echo.h"

#define PORT 22000

#define  EPOLL_SIZE 30

int main(int argc, char *argv[]) {
    int listen_fd, connection_fd;
    struct sockaddr client_address;
    socklen_t client_addr_len = sizeof client_address;

    if ((listen_fd = init_server(SOCK_STREAM, PORT)) < 0)
        return -1;

    int epfd;
    if ((epfd = epoll_create(1024)) < 0) {
        perror("create epoll failed");
        goto error_out;
    }

    struct epoll_event *events;
    events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event);

    while (1) {
        int event_cnt;
        if ((event_cnt = epoll_wait(epfd, events, EPOLL_SIZE, -1)) < 0) {
            perror("epoll wait error");
            goto error_out;
        }

        for (int i = 0; i < event_cnt; ++i) {
            int fd = events[i].data.fd;
            if (fd == listen_fd) {
                if ((connection_fd = accept(listen_fd, &client_address, &client_addr_len)) < 0)
                    goto error_out;
                // register connection fd
                event.events = EPOLLIN;
                event.data.fd = connection_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connection_fd, &event);
            } else {
                if (echo(fd) == 0) {
                    // disconnect
                    close(fd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                }
            }
        }
    }

    error_out:
    close(listen_fd);
    return -1;
}

