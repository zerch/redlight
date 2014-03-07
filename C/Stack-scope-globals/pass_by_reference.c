#include <stdio.h>

void add(int *p, int *q, int *r);

int main(int argc, char **argv)
{
    int a = 10, b = 20;
    int c;
    add(&a, &b, &c);
    printf("Sum of %d and %d is %d", a, b, c);
    return 0;
}

void add(int *p, int *q, int *r)
{
    *r = *p + *q;
}
