#include <raylib.h>
#include "game.h"

int main(void) {
    InitWindow(G_WIDTH, G_HEIGHT, "SpaceGame");
    SetTargetFPS(60);
    init();

    while (!WindowShouldClose()) {
        if (game.game_state == RUNNING) {
            update();
            draw();
        } else if (game.game_state == END)
            break;
    }

    deinit();
    CloseWindow();
    return 0;
}

