#include <raylib.h>
#include "objects.h"
#include "game.h"

void update(Player *player) {
    MoveObject(&player->base);
}

void draw(Player *player) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawText("Hello, World!", 190, 200, 20, BLACK);
    DrawTexture(player->base.texture, player->base.position.x, player->base.position.y, WHITE);
    EndDrawing();
}

int main(void) {
    InitWindow(G_HEIGHT, G_WIDTH, "SpaceGame");
    SetTargetFPS(60);
    Image img = LoadImage("../assets/Shippy.png");
    ImageFlipVertical(&img);

    Player player = {
        .health = 100, .base = {
            .texture = LoadTextureFromImage(img), .position = {100, 200}
        }
    };

    while (!WindowShouldClose()) {
        update(&player);
        draw(&player);
    }

    CloseWindow();

    return 0;
}
