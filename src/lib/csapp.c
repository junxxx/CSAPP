#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

/**
 * Robust I/O package
 *
 */

ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) /* Interrupted by sig handler return */
                nread = 0;      /* and call read() again */
            else
                return -1;      /* errno set by read() */
        }
        else if (nread == 0)
            break;              /* EOF */
        nleft -= nread;
        bufp += nread;
    }

    return (n - nleft);         /* Return >= 0*/
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd ,bufp, nleft)) <= 0) {
            if (errno == EINTR) /* Interrupted by sig handler return */
                nwritten = 0;   /* and call write() again */
            else
                return -1;      /* errno set by write() */
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0) {  /* Refill if buf is empty */
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));

        if (rp->rio_cnt < 0) {
            if (errno != EINTR) /* Enterrupted by sig handler return */
                return -1;
        }
        else if (rp->rio_cnt == 0)  /* EOF */
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf;   /* Reset buffer ptr */
    }

    /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
    cnt = n;
    if (rp->rio_cnt < n)
        cnt =rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n , rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1 ) {
            *bufp++ = c;
            if ( c == '\n') {
                n++;
                break;
            }
        } else if (rc == 0) {
            if (n == 1)
                return 0;   /* EOF, no data read */
            else
                break;      /* EOF, some data was read */
        }else 
            return -1;      /* Error */
    }
    *bufp = 0;
    return n-1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = rio_read(rp, bufp, nleft)) < 0)
            return -1;          /* errno set by read() */
        else if (nread == 0)
            break;              /* EOF */
        nleft -= nread;
        bufp += nread;
    }
    return n - nleft;           /* Return >= 0 */
}

int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    struct addrinfo hints, *lisp, *p;

    /* Get a list of potential server address */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;    /* open a connection */
    hints.ai_flags = AI_NUMERICSERV;    /* ... using a numeric port arg.*/
    hints.ai_flags |= AI_ADDRCONFIG;    /* recommended for connection */
    getaddrinfo(hostname, port, &hints, &lisp);

    /* walk the list for one that we can successfully connect to */
    for (p = lisp; p; p = p->ai_next) {
        /* create a socket descriptor */
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue;   /* socket failed, try the next */

        /* connect to the server */
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break;
        close(clientfd);    /* connect failed, try another */
    }

    /* clean up */
    freeaddrinfo(lisp);
    if (!p)                 /* all connects failed */
        return -1;
    else                    /* the last connect succeeded */
        return clientfd;    
}


int open_listenfd(char *port)
{
    struct addrinfo hints, *lisp, *p;
    int listenfd, optval=1;

    /* get a list of potential server adresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;        /* accept connections */
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;    /* ... on any IP address */
    hints.ai_flags |= AI_NUMERICSERV;               /* ... using port number */
    getaddrinfo(NULL, port, &hints, &lisp);

    /* walk the list for one that we can bind to */
    for (p = lisp; p; p = p->ai_next) {
        /*create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;       /* socket failed, try the next */

        /*eliminates "address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

        /* bind the descriptor to the address*/
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;          /* success*/
        close(listenfd);    /* bind failed, try the next */
    }

    /*clean up*/
    freeaddrinfo(lisp);
    if (!p)                 /* no address worked */ 
        return -1;

    /* make it listening socekt ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0){
        close(listenfd);
        return -1;
    }
    return listenfd;
}

