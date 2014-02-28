#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mechanics.h"

int Monster_attack(void *self, int damage)
{
    assert(self != NULL);
    
    Monster *monster = self;
    assert(monster != NULL);
   
    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if (monster->hit_points > 0) {
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}

int Monster_init(void *self)
{
    assert(self != NULL);
    
    Monster *monster = self;
    assert(monster != NULL);

    monster->hit_points = 10;
    return 1;
}

void *Room_move(void *self, Direction direction)
{
    assert(self != NULL);

    Room *room = self;
    assert(room != NULL);

    Room *next = NULL;

    if(direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
        assert(next != NULL);
    } else if (direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
        assert(next != NULL);
    } else if (direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
        assert(next != NULL);
    } else if (direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
        assert(next != NULL);
    } else {
        printf("You can't go that direction.");
        next = NULL;
    }

    if (next) {
        assert(next != NULL);
        next->_(describe)(next);
    }
    
    return next;
}

int Room_attack(void *self, int damage)
{
    assert(self != NULL);

    Room *room = self;
    assert(room != NULL);

    Monster *monster = room->bad_guy;

    if (monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

void *Map_move(void *self, Direction direction)
{
    assert(self != NULL);

    Map *map = self;
    assert(map != NULL);

    Room *location = map->location;
    assert(location != NULL);

    Room *next = NULL;

    next = location->_(move)(location, direction);

    if (next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self != NULL);

    Map *map = self;
    assert(map != NULL);

    Room *location = map->location;
    assert(location != NULL);

    return location->_(attack)(location, damage);
}

int process_input(Map *game, char input)
{
    assert (game != NULL);

    printf("\n> ");

    char ch;

    if (input) {
        ch = input;
    } else {
        ch = getchar();
        getchar(); // eat Enter
    }
    int damage = rand() % 4;

    switch(ch) {
        case -1:
            printf("Giving up? You suck.\n");
            return 0;
            break;

        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':
            game->_(attack)(game, damage);
            break;

        case 'l':
            printf("You can go:\n");
            if(game->location->north) printf("NORTH\n");
            if(game->location->south) printf("SOUTH\n");
            if(game->location->east) printf("EAST\n");
            if(game->location->west) printf("WEST\n");
            break;

        default:
            printf("What?: %d\n", ch);
            break;
        }
    return 1;
}



