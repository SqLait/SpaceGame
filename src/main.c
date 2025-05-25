#include <raylib.h>
#include "game.h"

int main(void) {
    InitWindow(G_HEIGHT, G_WIDTH, "SpaceGame");
    SetTargetFPS(60);
    init();

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}
