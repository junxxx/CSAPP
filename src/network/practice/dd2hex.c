#include "../../lib/csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    struct in_addr inaddr;
    int ok;
    uint32_t addr;

    if (argc <= 1) {
        printf("usage:%s %s\n", argv[0], "Ip");
        exit(0);
    }

    /**
     * pay attention to the byte order
     * inet_pton return to a binary IP in networking byte order (big-endian)
     */
    if ((ok = inet_pton(AF_INET, argv[1], &addr)) == 1) {
        inaddr.s_addr = ntohl(addr);
        printf("0x%x\n", inaddr.s_addr);
    } else if(ok == 0) {
        printf("invalid dotted decimal!\n");
    }
    
    exit(0);
}
