#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

void strip_whitespaces_and_newline(char *in)
{
    int i = 0;
    int j = 0;
    char rez[MAX_DATA];

    while (in[i] != '\n' && in[i] != '\0') {
        if (in[i] != ' ') {
            rez[j] = in[i];
            j++;
        }
        i++;
    }
    rez[j] = '\0';
    
    for (i = 0; i <= j; i ++) {
        in[i] = rez[i];
    }
}

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char **argv)
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;

    printf("What is your first name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read first name.");
    
    printf("What is your last name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");
    
    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, 
            "Do it right, that's not an option");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("------ Results -----\n");
    
    strip_whitespaces_and_newline(you.first_name);
    strip_whitespaces_and_newline(you.last_name);

    printf("First name: %s\n", you.first_name);
    printf("Last name: %s\n", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:
    return -1;
}
