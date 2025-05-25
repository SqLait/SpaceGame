#include "game.h"
#include "raylib.h"
#include <stdio.h>

Texture2D textures[2];
MemoryPool pool;
Object* bullet = NULL;

Game game = {
    .game_state = RUNNING,
    .update_game = true,
};

Object player = {
    .position = { (f32)G_WIDTH / 2, 900 },
    .texture_id = 0,
};

void init() {
    Image ship = LoadImage("assets/Shippy.png");
    if (ship.data == NULL) {
        TraceLog(LOG_ERROR, "Failed to load 'Shippy.png'");
        return;
    }
    ImageFlipVertical(&ship);
    textures[0] = LoadTextureFromImage(ship);
    UnloadImage(ship);

    Image star = LoadImage("assets/Star.png");
    if (star.data == NULL) {
        TraceLog(LOG_ERROR, "Failed to load 'Star.png'");
        return;
    }
    textures[1] = LoadTextureFromImage(star);
    UnloadImage(star);
    init_pool(&pool, sizeof(Object));
}

void update() {
    PlayerInput(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);
    if (IsKeyDown(KEY_SPACE) && bullet == NULL) {
        bullet = CreateNewBullet(&player, &textures[1], &pool);
    }
    if (bullet != NULL) {
        MoveBullet(bullet, &textures[1]);
        CheckBulletOutOfView(&bullet, &pool);
    }
}

void draw() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(textures[player.texture_id], player.position.x, player.position.y, WHITE);
    DrawRectangleLines(player.rect.x, player.rect.y, player.rect.width, player.rect.height, RED);
    if (bullet != NULL) {
        DrawTexture(textures[1], bullet->position.x, bullet->position.y, WHITE);
    }
    EndDrawing();
}

