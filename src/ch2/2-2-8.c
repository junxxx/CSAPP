#include <stdio.h>
float sum_elements(float a[], int length);
int main()
{
    float array[10] = { 1.2, 2.2, 2.3, 3.0};
    float sum1, sum2;
    int zero = 0;
    unsigned jude_num;
    jude_num = zero;
    jude_num = 0 - 1;
    printf("%f %x %u\n", (unsigned)zero -1,jude_num,jude_num);
    printf("%f %x\n", ((unsigned)0) -1);
    if( zero <= jude_num -1)
    {
        printf("zero <= jude_num\n");
    }
    printf("%x\n",jude_num);
    printf("%x\n",jude_num - 1);
    printf("%x\n",0 <=jude_num - 1);

    sum1 = sum_elements(array, 10);
    sum2 = sum_elements(array, 0);
    printf("%f\n",sum1);
    printf("%f\n",sum2);
    return 1;
}
float sum_elements(float a[], int length)
{
    int i;
    float result = 0;
    printf("i= %x length = %x length -1 = %d =%x\n", i, length, length -1 ,length -1);

    for(i = 0; i <= length -1; i++)
        result += a[i];
    return result;
}
