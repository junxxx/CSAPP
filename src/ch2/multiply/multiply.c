#include <stdio.h>
int main()
{
    int x = 4, y = 3, z;
    int yield_num;

    z = x * y;
    yield_num = (x << 1) + x;

    printf("z=%d   yidle_num=%d", z, yield_num);
    return 1;
}
