#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "types.h"

typedef struct {
    Texture2D texture; 
    Vector2 position;
} Object;

typedef struct {
    uint health;
    Object base;
} Player;

void MoveObject(Object *);
#endif
