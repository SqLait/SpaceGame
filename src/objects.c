#include "objects.h"

void MoveObject(Object *obj) {
    if (IsKeyDown(KEY_D)) obj->position.x += 2.0f;
    if (IsKeyDown(KEY_A)) obj->position.x -= 2.0f;
    if (IsKeyDown(KEY_W)) obj->position.y -= 2.0f;
    if (IsKeyDown(KEY_S)) obj->position.y += 2.0f;
}
