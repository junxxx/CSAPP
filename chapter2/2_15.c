#include <stdio.h>
int equal (int x, int y);
int main()
{
    int x = 3, y = 4, z = 3;
    printf("%d\n",equal(x, y));
    printf("%d\n",equal(x, z));
    printf("%d\n",equal(y, z));
    return 1;

}
int equal(int x, int y)
{
    return !(x^y);
}

