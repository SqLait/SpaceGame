#include <raylib.h>
#include "objects.h"
#include "game.h"

Texture2D textures[2];
Game game = {
    .game_state = RUNNING,
    .update_game = true,
    .player = { .position = { (f32)G_WIDTH / 2, 900 }, .texture_id = 0 }
};

void update() {
    MoveObject(&game.player);
}


void draw() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(textures[game.player.texture_id], game.player.position.x, game.player.position.y, WHITE);
    EndDrawing();
}

int main(void) {
    InitWindow(G_HEIGHT, G_WIDTH, "SpaceGame");
    SetTargetFPS(60);
    load_assets(textures);

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}
