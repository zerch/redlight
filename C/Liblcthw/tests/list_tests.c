#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
static List *list_two = NULL;
static List *list_three = NULL;
static List *list_four = NULL;
static List *list_five = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
    list = List_create();
    list_two = List_create();
    list_three = List_create();
    list_four = List_create();
    list_five = List_create();

    assert(list->first == NULL && list->last == NULL && 
            list->count == 0);
    mu_assert(list != NULL, "Failed to create list.");
    
    assert(list_two->first == NULL && list_two->last == NULL && 
            list_two->count == 0);
    mu_assert(list_two != NULL, "Failed to create list.");
    
    assert(list_three->first == NULL && list_three->last == NULL && 
            list_three->count == 0);    
    mu_assert(list_three != NULL, "Failed to create list.");
    
    assert(list_four->first == NULL && list_four->last == NULL && 
            list_four->count == 0);    
    mu_assert(list_four != NULL, "Failed to create list.");
    
    assert(list_five->first == NULL && list_five->last == NULL && 
            list_five->count == 0);    
    mu_assert(list_five != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_clear_destroy(list);
    
    assert(list->first == NULL && list->last == NULL);
    
    return NULL;
}

char *test_push_pop()
{
    assert(list->first == NULL && list->last == NULL && 
            list->count == 0);

    List_push(list, test1);
    
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_last(list) == test2, "Wrong last value.");
  
    List_push(list, test3);
    
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(val == test3, "Wrong value on pop.");
    
    val = List_pop(list);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(val == test2, "Wrong value on pop.");
    
    val = List_pop(list);
    assert(list->first == NULL && list->last == NULL && 
            list->count == 0);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    assert(list->first == NULL && list->last == NULL && 
            list->count == 0);

    List_unshift(list, test1);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_first(list) == test2, "Wrong first value.");

    List_unshift(list, test3);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);

    char *val = List_remove(list, list->first->next);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift()
{
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    assert(list->first != NULL && list->last != NULL && 
            list->count != 0);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    assert(list->first == NULL && list->last == NULL && 
            list->count == 0);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_copy()
{
    List_copy(list, list_two);
    
    assert(list_two->first != NULL && list_two->last != NULL && 
            list_two->count != 0);
    return NULL;
}

char *test_join()
{
    List_join(list, list_two, list_three);
    
    assert(list_three->first != NULL && list_three->last != NULL && 
            list_three->count != 0);
    
    return NULL;
}

char *test_split()
{
    List_split(list_four, list_five, list_three, list_three->first);

    return NULL;
}
char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_copy);
    mu_run_test(test_join);
    mu_run_test(test_split);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
