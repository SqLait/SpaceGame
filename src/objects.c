#include "objects.h"
#include "alloc.h"
#include "raylib.h"
#include "debug.h"
#include "dynlist.h"

void PlayerInput(Object *obj) {
    const float SPEED = 8;

    if (IsKeyDown(KEY_D)) obj->position.x += SPEED;
    if (IsKeyDown(KEY_A)) obj->position.x -= SPEED;
}

void UpdateRect(Rectangle *rect, Vector2 *position, Texture2D *texture) {
    *rect = (Rectangle){
        .height = texture->height,
        .width = texture->width,
        .x = (i32)position->x,
        .y = (i32)position->y
    };
}

Object *CreateNewBullet(Vector2 *position, Texture2D *texture, Pool *pool) {
    Object *bullet = pool_alloc(pool);
    ASSERT(bullet != NULL);

    bullet->position = *position;
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
    bullet->position.y -= 6;
    UpdateRect(&bullet->rect, &bullet->position, texture);
}

bool CheckBulletOutOfView(Object *bullet) {
    return bullet->position.y < -20;
}

Vector2 GetOrigin(Rectangle *rect, Vector2 *vec) {
    return (Vector2){
        .x = vec->x + (rect->width * 0.5f),
        .y = vec->y + (rect->height * 0.5f)
    };
}

i32 new_random(const u32 MAX) {
    return rand() % MAX + 1;
}

/*Updates all bullets in a list, will check for certain conditions*/
void update_bullets(Object **bullets, Texture2D *texture, Pool *pool) {
    for (i32 i = dynlist_length(bullets) - 1; i >= 0; i--) {
        if (CheckBulletOutOfView(bullets[i])) {
            Object* bullet = bullets[i];
            dynlist_removeat(bullets, i);
            pool_free(pool, bullet);
            continue; // Use continue to avoid use after free (UAF)
        }

        MoveBullet(bullets[i], texture);
    }
}
