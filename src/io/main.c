#include "../lib/csapp.h"
#include "../lib/csapp.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd1, fd2;
    char c;
    fd1 = open("foo.txt", O_RDONLY, 0);
    close(fd1);
    fd2 = open("baz.txt", O_RDWR|O_CREAT, S_IRUSR);
    printf("fd2 = %d\n", fd2);
   
    //reading and writing file
    /*
    while (read(STDIN_FILENO, &c, 1) != 0)
        write(STDOUT_FILENO, &c, 1);
    */
    while (rio_readn(STDIN_FILENO, &c, 1) != 0)
        rio_writen(fd2, &c, 1);
    
    exit(0);

    return 0;
}
