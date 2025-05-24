#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "alloc.h"
#include "types.h"
#include "dlist.h"

typedef struct Object {
    u8 texture_id; 
    Vector2 position;
    Rectangle rect;
} Object;

typedef struct Bullet {
    u8 texture_id; 
    Vector2 position;
    Rectangle rect;
    DNode list;
} Bullet;

void PlayerInput(Object *);
void UpdateRect(Rectangle *, Vector2 *, Texture2D *);
Object *CreateNewBullet(Object *, Texture2D *, MemoryPool *);
void MoveBullet(Object *, Texture2D *);
void CheckBulletOutOfView(Object **, MemoryPool *);
#endif
