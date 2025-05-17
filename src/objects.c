#include "objects.h"
#include "raylib.h"

void MoveObject(Object *obj) {
    const float SPEED = 8;
    if (IsKeyDown(KEY_D)) obj->position.x += SPEED;
    if (IsKeyDown(KEY_A)) obj->position.x -= SPEED;
    if (IsKeyDown(KEY_W)) obj->position.y -= SPEED;
    if (IsKeyDown(KEY_S)) obj->position.y += SPEED;
}

void UpdateRect(Rectangle *rect, Vector2 *position, Texture2D *texture) {
    *rect = (Rectangle){
        .height = texture->height,
        .width = texture->width,
        .x = (int)position->x,
        .y = (int)position->y
    };
}

Object CreateNewBullet(Object *obj, Texture2D *texture) {
    return (Object){
        .position = obj->position,
        .texture_id = 1,
        .rect = (Rectangle){
            .height = texture->height,
            .width = texture->width,
            .x = (int)obj->position.x,
            .y = (int)obj->position.y
        }
    };
}
