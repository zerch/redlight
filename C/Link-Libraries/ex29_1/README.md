cc -fPIC -c libex29.c -o libex29.o && cc -shared -o libex29.so libex29.o && cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29

    Were you paying attention to the bad code I have in the libex29.c functions? See how, even though I use a for-loop they still check for '\0' endings? Fix this so the functions always take a length for the string to work with inside the function.
    Take the c-skeleton skeleton, and create a new project for this exercise. Put the libex29.c file in the src/ directory. Change the Makefile so that it builds this as build/libex29.so.
    Take the ex29.c file and put it in tests/ex29_tests.c so that it runs as a unit test. Make this all work, which means you have to change it so that it loads the build/libex29.so file and runs tests similar to what I did manually above.
    Read the man dlopen documentation and read about all the related functions. Try some of the other options to dlopen beside RTLD_NOW.
