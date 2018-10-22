//
// Created by xy on 18-11-30.
//

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/**
 * However, gethostbyname and gethostbyaddr are now considered to be obsolete
 * they were removed from Version 4 of the Single UNIX Specification.
 */
int main(int argc, char *argv[]) {
    struct hostent *host;

    if (argc != 2) {
        printf("Usage: %s <addr>\n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
    if (!host)
        error_handling("gethostbyname error");

    printf("Official name: %s \n", host->h_name);
    for (int i = 0; host->h_aliases[i]; i++)
        printf("Aliases %d: %s \n", i + 1, host->h_aliases[i]);
    printf("Address type: %d \n", host->h_addrtype);
    for (int i = 0; host->h_addr_list[i]; i++)
        printf("IP address %d: %s \n", i + 1, inet_ntoa(*(struct in_addr *) host->h_addr_list[i]));

    return 0;
}

