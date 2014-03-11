#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

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

void read_char(char *in, int size)
{
    char c;
    int i = 0;
    scanf("%c", &c);
    while (c != '\n' && i < size) {
        in[i] = c;
        scanf("%c", &c);
        i++;
    }
    in[i] = '\0';
}

int main(int argc, char **argv)
{
    Person you = {.age = 0};
    char *in = NULL, age_s[MAX_DATA], eyes_s[MAX_DATA],
         income_s[MAX_DATA];
    int i = 0, age_i, eyes = -1;
    float inc_f;

    printf("What is your first name? ");
    read_char(you.first_name, MAX_DATA);
    check(you.first_name != NULL, "Failed to read first name.");
    
    printf("What is your last name? ");
    read_char(you.last_name, MAX_DATA);
    check(you.last_name != NULL, "Failed to read last name.");

    printf("How old are you? ");
    in = fgets(age_s, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read age");
    
    age_i = atoi(age_s);
    check(age_i > 0, "You have to enter a number.");
    
    you.age = age_i;

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");
    
    in = fgets(eyes_s, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to load eyes color number.");
    eyes = atoi(eyes_s);
    check(eyes > 0, "You have to enter a number.");
    
    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, 
            "Do it right, that's not an option");

    printf("How much do you make an hour? ");
    in = fgets(income_s, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to load income.");

    inc_f = atof(income_s);
    check(inc_f > 0, "You have to enter a floating point number");
    
    you.income = inc_f;
    
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
