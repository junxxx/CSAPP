#include <stdio.h>
int main()
{
    int x = -1;
    unsigned u = 2147483648;

    printf("x = %u = %d = %.2x\n", x, x, x);
    printf("u = %u = %d = %.2x\n", u, u, u);

    return 0;
}
