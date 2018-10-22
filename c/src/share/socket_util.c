//
// Created by xy on 19-1-5.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int get_address_str(struct sockaddr address, char * buf, size_t buf_len) {
    memset(buf, 0, buf_len);

    if (address.sa_family == AF_INET) {
        struct sockaddr_in *addr = (struct sockaddr_in *) &address;
        inet_ntop(AF_INET, &(addr->sin_addr), buf, (socklen_t) buf_len);

    } else if (address.sa_family == AF_INET6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *) &address;
        inet_ntop(AF_INET, &(addr6->sin6_addr), buf, (socklen_t) buf_len);
    }

    return 0;
}

int get_port(struct sockaddr address) {
    int port = 0;

    if (address.sa_family == AF_INET) {
        struct sockaddr_in *addr = (struct sockaddr_in *) &address;
        port = addr->sin_port;
    } else if (address.sa_family == AF_INET6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *) &address;
        port = addr6->sin6_port;
    }

    return port;
}
