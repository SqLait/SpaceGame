#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "alloc.h"
#include "types.h"

typedef struct Object {
    u8 texture_id; 
    Vector2 position;
    Rectangle rect;
} Object;

typedef struct Bullet {
    u8 texture_id; 
    Vector2 position;
    Rectangle rect;
} Bullet;

void PlayerInput(Object *);
void UpdateRect(Rectangle *, Vector2 *, Texture2D *);
Object *CreateNewBullet(Vector2 *, Texture2D *, Pool *);
void MoveBullet(Object *, Texture2D *);
bool CheckBulletOutOfView(Object *, Pool *);
Vector2 GetOrigin(Rectangle *, Vector2 *);
#endif
