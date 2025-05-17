#include <raylib.h>
#include <stdio.h>
#include "objects.h"
#include "types.h"
#include "game.h"

Texture2D textures[2];
Game game = {
    .game_state = RUNNING,
    .update_game = true,
};

Object player = {
    .position = { (f32)G_WIDTH / 2, 900 },
    .texture_id = 0,
};

void update() {
    MoveObject(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);
}

void draw() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(textures[player.texture_id], player.position.x, player.position.y, WHITE);
    DrawRectangleLines(player.rect.x, player.rect.y, player.rect.width, player.rect.height, RED);
    EndDrawing();
}

int main(void) {
    InitWindow(G_HEIGHT, G_WIDTH, "SpaceGame");
    SetTargetFPS(60);
    load_assets(textures);
    printf("length: %lu\n", ARRLEN(game.bullets));

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}
