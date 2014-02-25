// includes the standard input/output library
#include <stdio.h>
// includes the assert library ti use the assert() functiom
#include <assert.h>
// incldues the stdlib library to use malloc() and NULL methods
#include <stdlib.h>
// includes the string library to use the strdup() function
#include <string.h>

// declaring the struct name and parameters
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

// a method to create a person using the struct Person
struct Person *Person_create(char *name, int age, int height, int weight)
{
    // allocating memory for the new created struct with the size of struct
    struct Person *who = malloc(sizeof(struct Person));
    // checking if the memory allcoated is valid with assert and NULL
    assert(who != NULL);

    // the given values upon creating a new person will be added to the new struct
    // name is a duplicated string so to make sure that the new struct will own the
    // entire string. kind of like malloc
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;
    
    // return the new struct
    return who;
}

void Person_destroy(struct Person *who)
{
    // checking if struct's memory is valid
    assert(who != NULL);

    // using free() function to cleanup the memory where struct is located
    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    // prints structs details
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
            "Joe Alex", 32, 65, 140);
    struct Person *frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}
