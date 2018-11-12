#include <stdio.h>
int main()
{
    int a = 0xC3, b = 0x75, c = 0x87, d = 0x66;
    printf("a<<3 = %.2x\n", a << 3);
    printf("a>>2 = %.2x\n", a >> 2);
    printf("b<<3 = %.2x\n", b << 3);
    printf("b>>2 = %.2x\n", b >> 2);
    printf("c<<3 = %.2x\n", c << 3);
    printf("c<<3 = %.2x\n", c >> 2);
    printf("d>>2 = %.2x\n", d << 3);
    printf("d>>2 = %.2x\n", d >> 2);

    return 1; 
}
