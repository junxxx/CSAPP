#include "../lib/csapp.h"
#include "../lib/csapp.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = open_clientfd(host, port);
    rio_readinitb(&rio, clientfd);
    
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        rio_writen(clientfd, buf, strlen(buf));
        //may not receive data from server here
        rio_readlineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }
    close(clientfd);
    exit(0);
}
