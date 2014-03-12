#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

char* itoa(int num, char str[]) 
{
    char const digit[] = "0123456789";
    char* p = str;
    if (num < 0) {
        *p++ = '-';
        num *= -1;
    }
    int shifter = num;
    do { 
        ++p;
        shifter = shifter / 10;
    } while(shifter);
    *p = '\0';
    do { 
        *--p = digit[num%10];
        num = num / 10;
    } while(num);
    return str;
}

int write_string(char *in_string)
{
    /**in_string = calloc(1, MAX_DATA + 1);*/
    /*check_mem(*in_string);*/
   
    int rc = fputs(in_string, stdout);
    check(rc >= 0, "Output error.");

    return 0;
error:
    /*if (*in_string) free(*in_string);*/
    /**in_string = NULL;*/

    return -1;
}

int write_int(int in_int)
{   
    char object[MAX_DATA];
    (void)itoa(in_int, object);
    int rc = write_string(object);
    check(rc == 0, "Output error.");

    return 0;
error:
    return -1;
}

int write_scan(const char *fmt, ...)
{
    int i = 0;
    int rc = 0;
    int in_int = 0;
    int in_char;
    char *in_string = NULL;
    va_list argp;
    va_start(argp, fmt);

    for (i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            i++;
            switch(fmt[i]) {
                case '\0':
                    sentinel("Invalid format, you ended up with %%");
                    break;
                
                case 'd':
                    in_int = va_arg(argp, int);
                    rc = write_int(in_int);
                    check(rc == 0, "Failed to read int.");
                    break;
                
                case 'c':
                    in_char = va_arg(argp, int);
                    rc = fputc(in_char, stdout);
                    check(rc >= 0, "Failed to read char.");
                    break;
                
                case 's':
                    in_string = va_arg(argp, char *);
                    rc = write_string(in_string);
                    check(rc == 0, "Failed to read string.");
                    break;
                default:
                    sentinel("Invalid format.");
            }
        } else {
            fputc(fmt[i], stdout);
        }
        check(!ferror(stdout), "Output error.");
    }
    va_end(argp);

    return 0;
error:
    return -1;
}

int read_string(char **out_string, int max_buffer)
{
    *out_string = calloc(1, max_buffer + 1);
    check_mem(*out_string);

    char *result = fgets(*out_string, max_buffer, stdin);
    check(result != NULL, "Input error.");

    return 0;

error:
    if (*out_string) free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(int *out_int)
{
    char *input = NULL;
    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "Failed to read number. ");

    *out_int = atoi(input);

    free(input);
    return 0;

error:
    if(input) free(input);
    return -1;
}

int read_scan(const char *fmt, ...)
{
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    va_list argp;
    va_start(argp, fmt);

    for (i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            i++;
            switch(fmt[i]) {
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;

                case 'd':
                    out_int = va_arg(argp, int *);
                    rc = read_int(out_int);
                    check(rc == 0, "Failed to read int.");
                    break;

                case 'c':
                    out_char = va_arg(argp, char *);
                    *out_char = fgetc(stdin);
                    break;

                case 's':
                    max_buffer = va_arg(argp, int);
                    out_string = va_arg(argp, char **);
                    rc = read_string(out_string, max_buffer);
                    check(rc == 0, "Failed to read string");
                    break;

                default:
                    sentinel("Invalid format.");
            }
        } else {
            fgetc(stdin);
        }

        check(!feof(stdin) && !ferror(stdin), "Input error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int main(int argc, char **argv)
{
    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    int age = 0;

    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name);
    check(rc == 0, "Failed to read first name.");

    printf("What's your initial? ");
    rc = read_scan("%c\n", &initial);
    check(rc == 0, "Failed to read initial.");

    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "Failed to read last name.");

    printf("How old are you? ");
    rc = read_scan("%d", &age);
    check(rc == 0, "Failed to read age");

    printf("----- Results #1 -----\n");
    printf("First name: %s", first_name);
    printf("Initial: %c\n", initial);
    printf("Last name: %s", last_name);
    printf("Age: %d\n", age);
    
    write_scan("\n----- Results #2 -----\n");
    
    rc = write_scan("First name: %s", first_name);
    check(rc == 0, "Failed to write first name.");
    
    rc = write_scan("Initial: %c\n", initial);
    check(rc == 0, "Failed to write initial.");
    
    rc = write_scan("Last name: %s", last_name);
    check(rc == 0, "Failed to write last name.");
    
    rc = write_scan("Age: %d\n", age);
    check(rc == 0, "Failed to write age");
    
    free(first_name);
    free(last_name);
    
    return 0;

error:
    return -1;
}


