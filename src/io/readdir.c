#include "../lib/csapp.h"
#include "../lib/unixerr.h"
#include "../lib/unixerr.c"

int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    if (argc <= 1) {
        printf("usage: %s %s\n", argv[0], "directory");
        exit(1);
    }

    streamp = opendir(argv[1]);
    if (streamp == NULL) {
        unix_error("readdir error");
    }

    errno = 0;
    while ((dep = readdir(streamp)) != NULL) {
        printf("Found file: %s\n", dep->d_name);
    }

    if (errno != 0)
        unix_error("readdir error");

    closedir(streamp);
    exit(0);
}
