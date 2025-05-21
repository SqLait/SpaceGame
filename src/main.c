#include <raylib.h>
#include "objects.h"
#include "types.h"
#include "game.h"
#include "alloc.h"

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

void update() {
    PlayerInput(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);
    if (IsKeyDown(KEY_SPACE)) {
        bullet = CreateNewBullet(&player, &textures[1], &pool);
    }
    if (bullet != NULL) {
        MoveBullet(bullet, &textures[1]);
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

int main(void) {
    InitWindow(G_HEIGHT, G_WIDTH, "SpaceGame");
    SetTargetFPS(60);
    load_assets(textures);
    init_pool(&pool, sizeof(Object));

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}
