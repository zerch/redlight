#include <stdio.h>

int add(int p, int q);

int main(int argc, char **argv)
{
    int a = 10, b = 20;
    int c = add(a,b);
    printf("\nSum of %d and %d is %d", a, b, c);
    return 0;
}

int add(int p, int q)
{
    int result = p + q;
    return (result);
}
    
