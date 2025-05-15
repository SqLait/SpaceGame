#include <raylib.h>
#include "objects.h"
#include "game.h"

void update() {
}

void draw() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    EndDrawing();
}

int main(void) {
    InitWindow(G_HEIGHT, G_WIDTH, "SpaceGame");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}
