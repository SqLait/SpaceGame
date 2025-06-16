#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "alloc.h"
#include "types.h"
#include "dynlist.h"

typedef struct Object {
    u8 texture_id; 
    Vector2 position;
    Rectangle rect;
} Object;

void PlayerInput(Object *);
void UpdateRect(Rectangle *, Vector2 *, Texture2D *);
Object *CreateNewBullet(Vector2 *, Texture2D *, Allocator *);
Vector2 GetOrigin(Rectangle *, Vector2 *);
i32 new_random(const u32);
void update_bullets(Object **, Texture2D *, Allocator *);
void update_enemies(Object **, Texture2D *, Allocator *);
Object *CreateNewEnemy(Vector2 *, Texture2D *, Allocator *);
void CheckBulletCollision(Object **, Allocator *, Object **, Allocator *);
#endif
