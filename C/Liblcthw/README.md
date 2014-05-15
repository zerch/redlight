
    You can make List_clear_destroy more efficient by using LIST_FOREACH and doing both free calls inside one loop.
    You can add asserts for preconditions that it isn't given a NULL value for the List *list parameters.
    You can add invariants that check the list's contents are always correct, such as count is never < 0, and if count > 0 then first isn't NULL.
    You can add documentation to the header file in the form of comments before each struct, function, and macro that describes what it does.

These amount to going through the defensive programming practices I talked about and "hardening" this code against flaws or improving usability. Go ahead and do these things, then find as many other ways to improve the code.
Extra Credit

    Research double vs. single linked lists and when one is preferred over the other.
    Research the limitations of a double linked list. For example, while they are efficient for inserting and deleting elements, they are very slow for iterating over them all.
    What operations are missing that you can imagine needing? Some examples are copying, joining, splitting. Implement these operations and write the unit tests for them.

