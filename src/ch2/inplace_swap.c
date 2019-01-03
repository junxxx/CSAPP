#include <stdio.h>
void inplace_swap(int *x, int *y);
void reverse_array(int a[], int cnt);
void display(int array[], int cnt);
int main()
{
    int a = 3, b = 5;
    int array_a[] = {1,2,3,4};
    int array_b[] = {1,2,3,4,5};
    inplace_swap(&a, &b);
    printf("a=%d, b=%d",a,b);
    display(array_a,4);
    display(array_b,5);
    reverse_array(array_a, 4);
    reverse_array(array_b, 5);
    display(array_a,4);
    display(array_b,5);


    return 1;
}

void inplace_swap(int *x, int *y)
{
    printf("<----------------------\n");
    printf("x=%.2x y=%.2x\n", *x, *y);
    *y = *x ^ *y;
    printf("x=%.2x y=%.2x\n", *x, *y);
    *x = *x ^ *y;
    printf("x=%.2x y=%.2x\n", *x, *y);
    *y = *x ^ *y;
    printf("x=%.2x y=%.2x\n", *x, *y);
    printf("---------------------->\n");
}

void reverse_array(int a[], int cnt)
{
    int first, last;
    for(first  = 0, last = cnt-1; first < last; first++,last--)
        inplace_swap(&a[first], &a[last]);

}

void display(int array[], int cnt)
{
    int i;
    for(i=0; i < cnt; i++)
        printf("%d  ", array[i]);
    printf("\n");
}
