#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "types.h"

typedef struct Object {
    u8 texture_id; 
    Vector2 position;
    Rectangle rect;
} Object;

void MoveObject(Object *);
#endif
