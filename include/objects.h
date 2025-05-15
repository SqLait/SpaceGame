#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "types.h"

typedef struct Object {
    u8 texture_id; 
    Vector2 position;
} Object;

typedef struct Player {
    uint health;
    Object base;
} Player;

void MoveObject(Object *);
#endif
