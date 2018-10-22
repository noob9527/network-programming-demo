//
// Created by xy on 19-1-5.
//

#ifndef NETWORK_PROGRAMMING_DEMO_SHARE_H
#define NETWORK_PROGRAMMING_DEMO_SHARE_H

// socket
int *get_address_str(struct sockaddr, char * buf, size_t buf_len);
int get_port(struct sockaddr);

// error
void err_msg(const char *, ...);

#endif //NETWORK_PROGRAMMING_DEMO_SHARE_H
