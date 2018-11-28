#include "../../lib/csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    /**
     * pay attention to the byte order
     */
    struct in_addr inaddr;
    uint32_t addr;
    unsigned char dst[INET_ADDRSTRLEN];

    if (argc <= 1) {
        printf("usage:%s %s\n", argv[0], " hex format string");
        exit(0);
    }

    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);
    inet_ntop(AF_INET, &inaddr, dst, INET_ADDRSTRLEN);
    printf("%s\n", dst);
    exit(0);
}
