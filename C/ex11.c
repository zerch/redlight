#include <stdio.h>

int main(int argc, char **argv)
{
    // go through each string in argv

    int i = 1;
    while ( i < argc ) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }
    
    // let's make our own array of strings
    printf("arg array size is %d.\n", i);
    
    char *states[argc];
    i = 1;
    while(i < argc) {
        states[i] = argv[i];
        i++;
    }

    i = 1; // watch for this
    while ( i < argc ) {
        printf("states %d: %s\n", i, states[i]);
        i++;
    }

    return 0;
}
