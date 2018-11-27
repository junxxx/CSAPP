#include <stdio.h>
#include <stdlib.h>
#include "../lib/csapp.h"

int main(int argc, char **argv)
{
    struct stat stats;
    char *type, *readok;

    stat(argv[1], &stats);
    if (S_ISREG(stats.st_mode))
        type = "regular";
    else if (S_ISDIR(stats.st_mode))
        type = "directory";
    else
        type = "other";
    if ((stats.st_mode && S_IRUSR))
        readok = "yes";
    else
        readok = "no";

    printf("type: %s, read %s\n", type, readok);

    exit(0);
    return 0;
}
