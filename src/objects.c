#include "objects.h"
#include "alloc.h"
#include "game.h"
#include "raylib.h"
#include "debug.h"
#include "dynlist.h"

void PlayerInput(Object *obj) {
    const float SPEED = 12;

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

Object *CreateNewBullet(Vector2 *position, Texture2D *texture, Allocator *a) {
    Object *bullet = a->alloc(a, _);
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


Object *CreateNewEnemy(Vector2 *position, Texture2D *texture, Allocator *a) {
    Object *bullet = a->alloc(a, _);
    ASSERT(bullet != NULL);

    bullet->position = *position;
    bullet->texture_id = 2;
    bullet->rect = (Rectangle){
        .height = texture->height,
        .width = texture->width,
        .x = bullet->position.x,
        .y = bullet->position.y,
    };

    return bullet;
}

static void MoveBullet(Object *bullet, Texture2D *texture) {
    bullet->position.y -= 8;
    UpdateRect(&bullet->rect, &bullet->position, texture);
}

static void MoveEnemy(Object *enemy, Texture2D *texture) {
    enemy->position.y += 6;
    UpdateRect(&enemy->rect, &enemy->position, texture);
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

/*I know this is a brute force solution but I don't care*/
void CheckEnemyCollision(Object **enemies, Allocator *a_enemy, Object **bullets, Allocator *a_bullets, Object *player) {
    for (size i = 0; i < dynlist_length(enemies); i++) {
        if (CheckCollisionRecs(enemies[i]->rect, player->rect)) {
            Object* enemy = enemies[i];
            dynlist_removeat(enemies, i);
            a_enemy->free(a_enemy, enemy);
            game.game_state = END;
        }

        for (size j = 0; j < dynlist_length(bullets); j++) {
            if (CheckCollisionRecs(enemies[i]->rect, bullets[j]->rect)) {
                Object* bullet = bullets[j];
                dynlist_removeat(bullets, j);
                a_bullets->free(a_bullets, bullet);

                Object* enemy = enemies[i];
                dynlist_removeat(enemies, i);
                a_enemy->free(a_enemy, enemy);
                continue;
            }
        }
    }
}

static bool CheckObjectOutOfView(Object *bullet, i32 view) {
    return bullet->position.y < view;
}

static bool CheckBulletOutOfView(Object *bullet, i32 view) {
    return bullet->position.y > view;
}

/*Updates all bullets in a list, will check for certain conditions*/
void update_bullets(Object **bullets, Texture2D *texture, Allocator *a) {
    for (i32 i = dynlist_length(bullets) - 1; i >= 0; i--) {
        if (CheckObjectOutOfView(bullets[i], -20)) {
            Object* bullet = bullets[i];
            dynlist_removeat(bullets, i);
            a->free(a, bullet);
            continue; // Use continue to avoid use after free (UAF)
        }

        MoveBullet(bullets[i], texture);
    }
}

void update_enemies(Object **enemies, Texture2D *texture, Allocator *a) {
    for (i32 i = dynlist_length(enemies) - 1; i >= 0; i--) {

        if (CheckBulletOutOfView(enemies[i], G_HEIGHT + 20)) {
            Object* enemy = enemies[i];
            dynlist_removeat(enemies, i);
            a->free(a, enemy);
            continue; // Use continue to avoid use after free (UAF)
        }

        MoveEnemy(enemies[i], texture);
    }
}
