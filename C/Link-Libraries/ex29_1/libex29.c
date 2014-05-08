#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "dbg.h"

int print_a_message(const char *msg, const int len)
{
    assert(msg != NULL && "message can't be NULL");
    
    int i;
    int max;
    const char *pointer = msg;

    while(*(pointer+max)) max++;

    check(msg[max] == '\0', "String termination problem!");
    check(len >= 0, 
            "Please enter a positive length for message\n");
    
    if(len-1 <= max) max = len;
    
    printf("A STRING: ");
    for(i = 0; i < max; i++) putchar(msg[i]);

    return 0;
error:
    return 1;
}


int uppercase(const char *msg, const int len)
{
    assert(msg != NULL && "message can't be NULL");
    
    int i;
    int max;
    const char *pointer = msg;

    while (*(pointer+max)) max++;

    check(msg[max] == '\0', "String termination problem!");
    check(len >= 0, 
            "Please enter a positive length for message\n");
    
    if(len-1 <= max) max = len;
       
    for(i = 0; i < max; i++) putchar(toupper(msg[i]));

    return 0;
error:
    return -1;
}

int lowercase(const char *msg, const int len)
{
    assert(msg != NULL && "message can't be NULL");
    
    int i;
    int max;
    const char *pointer = msg;

    while (*(pointer+max)) max++;

    check(msg[max] == '\0', "String termination problem!");
    check(len >= 0, 
            "Please enter a positive length for message\n");
    
    if(len-1 <= max) max = len;
       
    for(i = 0; i < max; i++) putchar(tolower(msg[i]));

    return 0;
error:
    return -1;
}

int fail_on_purpose(const char *msg, const int len)
{
    return 1;
}
