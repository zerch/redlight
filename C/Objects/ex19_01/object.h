// ifndef = if not defined
// checks if there is already a #define _object_h
#ifndef _object_h
#define _object_h

typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
    char *description;
    int (*init)(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

// this is a macro
// a shorter way for code on the right
// use code on left to spit out code on right
// T##Proto = concat Proto at the end of T
// ex: NEW(Room, "Hello.") would create RoomProto
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)

//help to write obj->_(blah) instead of obj->proto.blah
#define _(N) proto.N

#endif
