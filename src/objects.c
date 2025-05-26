#include "objects.h"
#include "poolalloc.h"
#include "raylib.h"
#include "debug.h"

void PlayerInput(Object *obj) {
    const float SPEED = 8;

    if (IsKeyDown(KEY_D)) obj->position.x += SPEED;
    if (IsKeyDown(KEY_A)) obj->position.x -= SPEED;
}

void UpdateRect(Rectangle *rect, Vector2 *position, Texture2D *texture) {
    *rect = (Rectangle){
        .height = texture->height,
        .width = texture->width,
        .x = (int)position->x,
        .y = (int)position->y
    };
}

Object *CreateNewBullet(Object *player, Texture2D *texture, Pool *pool) {
    Object *bullet = (Object *)pool_alloc(pool);
    ASSERT(bullet != NULL);

    bullet->position = player->position;
    bullet->texture_id = 1;
    bullet->rect = (Rectangle){
        .height = texture->height,
        .width = texture->width,
        .x = bullet->position.x,
        .y = bullet->position.y,
    };

    return bullet;
}

void MoveBullet(Object *bullet, Texture2D *texture) {
    bullet->position.y -= 4;
    UpdateRect(&bullet->rect, &bullet->position, texture);
}

void CheckBulletOutOfView(Object **bullet, Pool *pool) {
    if ((*bullet)->position.y < -10) {
        pool_free(pool, bullet);
        *bullet = NULL;
    }
}
