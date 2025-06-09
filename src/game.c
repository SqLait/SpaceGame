#include "game.h"
#include "objects.h"
#include "raylib.h"
#include "alloc.h"
#include "debug.h"
#include "dynlist.h"
#include <time.h>

Texture2D textures[2];
Pool* pool;
Object* bullets = NULL;

Game game = {
    .game_state = RUNNING,
    .update_game = true,
    .delta_time = 0,
};

Object player = {
    .position = { (f32)G_WIDTH / 2, 900 },
    .texture_id = 0,
};

void init() {
    Image ship = LoadImage("assets/Shippy.png");
    ASSERT_MSG(ship.data != NULL, "Failed to load 'Shippy.png'");

    ImageFlipVertical(&ship);
    textures[0] = LoadTextureFromImage(ship);
    UnloadImage(ship);

    Image star = LoadImage("assets/Star.png");
    ASSERT_MSG(star.data != NULL, "Failed to load 'Star.png'");

    textures[1] = LoadTextureFromImage(star);
    UnloadImage(star);

    pool = pool_new(6);
    bullets = dynlist_init(Object);
}

void deinit() {
    pool_close(pool);
    dynlist_destroy(bullets);
}

void update() {
    PlayerInput(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);
    if (IsKeyDown(KEY_SPACE)) {
        Vector2 center = GetOrigin(&player.rect, &player.position);
        Object* bullet = CreateNewBullet(&center, &textures[1], pool);
        dynlist_push(bullets, *bullet);
    }

    for (size i = 0; i < dynlist_length(bullets); i++) {
        MoveBullet(&bullets[i], &textures[bullets[i].texture_id]);
        CheckBulletOutOfView(&bullets[i], pool);
    }
}

void draw() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(textures[player.texture_id], player.position.x, player.position.y, WHITE);
    DrawRectangleLines(player.rect.x, player.rect.y, player.rect.width, player.rect.height, RED);
    for (size i = 0; i < dynlist_length(bullets); i++) {
        DrawTexture(textures[bullets[i].texture_id], bullets[i].position.x, bullets[i].position.y, WHITE);
    }
    EndDrawing();
}

