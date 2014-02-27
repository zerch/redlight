/**
 * Write another sorting algorithm, then change test_sorting so that it takes 
 * both an arbitrary sort function and the sort function's callback comparison.
 * Use it to test both of your algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);
typedef int* (*sort_func)(int *numb, int count, compare_cb cmp);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if (!target) die ("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (i=0; i < count; i++) {
        for (j = 0; j < count -1; j++) {
            if (cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }
    return target;
}
/**
 * Insertion sort
 */
int *insertion_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int ind = 0;
    int *target = malloc(count * sizeof(int));
    
    if (!target) die ("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 1; i < count; i++) {
        ind = i;
        while (ind > 0 && cmp(target[ind], target[ind-1]) < 0) {
            temp = target[ind];
            target[ind] = target[ind - 1];
            target[ind - 1] = temp;

            ind--;
        }
    }
    return target;
}

int sorted_order(int a, int b)
{
    return a-b;
}

int reverse_order(int a, int b)
{
    return b-a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * User to test that we are sorting things correctly
 * by doing the sort and printing it out
 */
void test_sorting(int *numbers, int count, compare_cb cmp, sort_func sf)
{
    int i = 0;
    int *sorted = sf(numbers, count, cmp);

    if (!sorted) die("Failed to sort as requested.");

    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    free(sorted);
    
    unsigned char *data = (unsigned char *)cmp;
    for (i = 0; i < 25; i++) {
        printf("%02x:", data[i]);
    }
    printf("\n");

}

int main(int argc, char *argv[])
{
    if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc -1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die ("Memory error.");

    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order, bubble_sort);
    test_sorting(numbers, count, reverse_order, bubble_sort);
    test_sorting(numbers, count, strange_order, bubble_sort);
    
    test_sorting(numbers, count, sorted_order, insertion_sort);
    test_sorting(numbers, count, reverse_order, insertion_sort);
    test_sorting(numbers, count, strange_order, insertion_sort);

    free(numbers);

    return 0;
}

