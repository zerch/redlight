#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ex23_01.h"
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
    int i = 0;
    for (i = 0; i < count; i++) {
        to[i] = from[i];
    }
    return i;
}

int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 31) / 32;
        switch(count % 32) {
            case 0: do { *to++ = *from++;
                        SEVEN_AT_ONCE(3);
                        EIGHT_AT_ONCE(2);
                        EIGHT_AT_ONCE(1);
                        EIGHT_AT_ONCE(0);
                      } while (--n > 0);
        }
    }
    return count;
}

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 31) / 32;
        switch(count % 32) {
            case 0:
again: *to++ = *from++;
            SEVEN_AT_ONCE(3);
            EIGHT_AT_ONCE(2);
            EIGHT_AT_ONCE(1);
            EIGHT_AT_ONCE(0);
            if (--n > 0) goto again;
        }
    }

    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for (i = 0; i < count; i++) {
        if (data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}

int main(int argc, char **argv)
{
    char from[1000] = {'a'};
    char to[1000] = {'c'};
    int rc = 0;

    struct timeval stop, start;
    // setup the from to have some stuff
    memset(from, 'x', 1000);
    // set it to a failure mode
    memset(to, 'y', 1000);
    check(valid_copy(to, 1000, 'y'), "Not initialized right.");

    // use normal copy to
    gettimeofday(&start, NULL);
    rc = normal_copy(from, to, 1000);
    gettimeofday(&stop, NULL);
    printf("\nNormal copy took %lu microseconds", 
            stop.tv_usec - start.tv_usec);
    check(rc == 1000, "Normal copy failed: %d", rc);
    check(valid_copy(to, 1000, 'x'), "Normal copy failed");

    // reset
    memset(to, 'y', 1000);

    // duff's version
    gettimeofday(&start, NULL);
    rc = duffs_device(from, to, 1000);
    gettimeofday(&stop, NULL);
    printf("\nDuff copy took %lu microseconds", 
            stop.tv_usec - start.tv_usec);
    check(rc == 1000, "Duff's device failed: %d", rc);
    check(valid_copy(to, 1000, 'x'), "Duff's device failed copy.");

    // reset
    memset(to, 'y', 1000);
    gettimeofday(&start, NULL);
    rc = zeds_device(from, to, 1000);
    gettimeofday(&stop, NULL);
    printf("\nZed copy took %lu microseconds", 
            stop.tv_usec - start.tv_usec);
    check(rc == 1000, "Zeds device failed: %d", rc);
    check(valid_copy(to, 1000, 'x'), "Zed's device failed copy.");
    
    return 0;
error:
    return 1;
}

