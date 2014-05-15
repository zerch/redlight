#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{   
    LIST_FOREACH(list, first, next, cur, node) {
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur, node) {
        free(cur->value);
    }
}

void List_clear_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur, node) {
        free(cur->value);
        if (cur->prev) {
            free(cur->prev);
        }
    }

    list->count = 0;
    free(list->last);
    free(list);
}

void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}


void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;
error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL.");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, 
                "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if(node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, 
                "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

void List_split(List *list_one, List *list_two, List *list, ListNode *node)
{
    
    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL.");

    if(node == list->first && node == list->last) {
        List_copy(list, list_one);
    } else if(node == list->first) {
        List_copy(list, list_two);
        list_two->first->next->prev = NULL;
        List_remove(list_two, list_two->first);
        list_one->first = list->first;
        list_one->first->next = NULL;
    } else if(node == list->last) {
        List_copy(list, list_one);
        list_two->first = NULL;
    } else {
        List_copy(list, list_two);
        List_copy(list, list_one);
        
        LIST_FOREACH(list, first, next, cur1, node1) {
            if (node1 != node) {
                List_shift(list_two);
            } else {
                List_shift(list_two);
                break; 
            }
        }
        int i = 0;
        for (i = 0; i < list_two->count; i++){
            List_pop(list_one);
        }
    }
    
    debug_list_split(list, list_one, list_two);

error:
    return;
}

void debug_list_split(List *list, List *list_one, List *list_two)
{
    List_show(list);
    List_show(list_one);
    List_show(list_two);
    printf("\n\n");
}


void List_show(List *list)
{
    printf("\n=====");
    LIST_FOREACH(list, first, next, cur, node) {
        printf("\n%s", cur->value);
    }
    printf("\n=====");
}
void List_copy(List *list_one, List *list_two)
{
    List_destroy(list_two);
    list_two = List_create();

    LIST_FOREACH(list_one, first, next, cur_copy, node) {
        List_push(list_two, cur_copy->value);
    }
    list_two->count = list_one->count;
}

void List_join(List *list_one, List *list_two, List *list)
{
    LIST_FOREACH(list_one, first, next, cur1, node1) {
        List_unshift(list, cur1->value);
    }
    
    LIST_FOREACH(list_two, first, next, cur2, node2) {
        List_unshift(list, cur2->value);
    }
     
    list->count = list_one->count + list_two->count;
}


