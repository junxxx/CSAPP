#include <stdio.h>
#include <limits.h>
int main()
{
    unsigned u_negation_num, u_num_one = 3;
    int t_negation_num, t_num = 5, t_min = INT_MIN;
    u_negation_num = (unsigned)-u_num_one;
    t_negation_num = -t_num;
    printf("unsigned %u = %d, it's negative = %u hex=%x\n", u_num_one, u_num_one, u_negation_num, u_negation_num);
    printf("int %d  it's negative = %d hex= %x\n", t_num, t_negation_num, t_negation_num);
    printf("int_min %d  it's negative = %d hex= %x\n", t_min, t_min, -t_min);
    return 1;
}
