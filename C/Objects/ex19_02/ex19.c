#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};

int Map_init(void *self)
{
    assert(self != NULL);

    Map *map = self;
    assert(map != NULL);

    // make some rooms for a small map
    Room *courtyard = NEW(Room, "A big royal courtyard");
    assert(courtyard != NULL);
    
    Room *servant_house = NEW(Room, "The Servant's Home. You find a gold key");
    assert(servant_house != NULL);
    
    Room *warehouse = NEW(Room, "The king's warehouse and treasure vault. A Giant rat attacks you!");
    assert(warehouse != NULL);
    
    Room *gate = NEW(Room, "You reached the gates of Great King Pancreas holiday castle");
    assert(gate != NULL);
    
    Room *blacksmith = NEW(Room, "The blacksmith. You find a halberd!");
    assert(warehouse != NULL);
    
    Room *cemetery = NEW(Room, "The Cemetery. You are attacked by zombies!");
    assert(cemetery != NULL);
       
    Room *hall = NEW(Room, "The great Hall");
    assert(hall != NULL);

    Room *throne = NEW(Room, "The throne room");
    assert(throne != NULL);

    Room *arena = NEW(Room, "The arena, with the Minotaur");
    assert(arena != NULL);

    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
    assert(kitchen != NULL);

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "The evil Minotaur");
    cemetery->bad_guy = NEW(Monster, "A pack of zombies");
    warehouse->bad_guy = NEW(Monster, "A giant rat");

    // setup the map rooms
    courtyard->north = hall;
    courtyard->south = gate;
    courtyard->east = servant_house;
    courtyard->west = warehouse;

    warehouse->east = courtyard;

    servant_house->west = courtyard;

    gate->north = courtyard;
    gate->east = cemetery;
    gate->west = blacksmith;

    blacksmith->east = gate;

    cemetery->west = gate;

    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    // start the map and the character off in the hall
    map->start = gate;
    map->location = gate;
    
    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int main(int argc, char *argv[])
{
    // simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Hall of the Minotaur.");
    assert(game != NULL);

    printf("You enter the ");
    game->location->_(describe)(game->location);
    
    if (argc > 1) {
        int i = 1;
        for (i = 1; i < argc; i++) {
            process_input(game, argv[i][0]);
        }
    } else {
        while(process_input(game, '\0')) 
        {}
    }

    return 0;
}
