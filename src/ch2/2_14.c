#include <stdio.h>
int main()
{
    int x = 0x66, y = 0x39;
    printf("x=%.2x, y = %.2x\n", x, y);
    printf("x&y = %.2x\n", x&y);
    printf("x&&y = %.2x\n", x&&y);
    printf("x|y = %.2x\n", x|y);
    printf("x||y = %.2x\n", x||y);
    printf("~x|~y = %.2x\n", ~x|~y);
    printf("!x||!y = %.2x\n", !x||!y);
    printf("x&!y = %.2x\n", x&!y);
    printf("x&&~y = %.2x\n", x&&~y);
    return 1;
}
