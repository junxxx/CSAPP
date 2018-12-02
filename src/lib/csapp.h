#ifndef __CSSAPP_H__
#define __CSSAPP_H__
#include <sys/types.h>

#ifndef RIO_BUFSIZE
#define RIO_BUFSIZE 8192
#endif
#ifndef MAXLINE
#define MAXLINE 512
#endif
#ifndef LISTENQ 
#define LISTENQ 8
#endif

typedef struct {
    int rio_fd;                 /* Descriptor for this internal buf */
    int rio_cnt;                /* Unread bytes in internal buf */
    char *rio_bufptr;           /* Next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE];  /* Internal buferr */
} rio_t;

typedef struct sockaddr SA;


//Robust I/O
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t h);

void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

/**
 * helper function for the sockets interface
 */
int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);

#endif
