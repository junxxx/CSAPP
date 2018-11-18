#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//Robust I/O
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t h);
