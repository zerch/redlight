/* -Rewrite this program to use a function for each of the ways you're printing 
 * out things. Try to pass pointers to these functions so they work on the data.
*/
#include <stdio.h>

void print_years_one(int i, int count,\
        int ages[], char *names[]);
void print_years_two(int i, int count,\
        int *cur_age, char **cur_name);
void print_years_three(int i, int count,\
        int ages[], char *names[]);
void print_years_four(int count,\
        int *cur_age, char **cur_name,\
        int ages[], char *names[]);

void print_years_one(int i, int count,\
        int ages[], char *names[])
{
    for ( i = 0; i < count; i++)
    {
        printf("%s has %d years alive.\n", 
                names[i], ages[i]);
    }
    printf("---\n");
}

void print_years_two(int i, int count,\
        int *cur_age, char **cur_name)
{
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name + i), *(cur_age + i));
    }
    printf("---\n");
}

void print_years_three(int i, int count,\
        int ages[], char *names[])
{
    int *cur_age = ages;
    char **cur_name = names;
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }
    printf("---\n");
}

void print_years_four(int count,\
        int *cur_age, char **cur_name,\
        int ages[], char *names[])
{
    for(cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

}

int main(int argc, char **argv)
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    int *cur_age = ages;
    char **cur_name = names;

    print_years_one(i, count, ages, names);
    print_years_two(i, count, cur_age, cur_name);
    print_years_three(i, count, ages, names);
    print_years_four(count, cur_age, cur_name, ages, names);

    return 0;
}
