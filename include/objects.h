#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "types.h"

typedef struct Object {
    Texture2D texture; 
    Vector2 position;
} Object;

typedef struct Player {
    uint health;
    Object base;
} Player;

void MoveObject(Object *);
#endif
