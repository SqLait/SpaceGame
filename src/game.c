#include "game.h"
#include "raylib.h"
#include <stdio.h>

void load_assets(Texture2D *textures) {
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
    printf("Nigbob");
}

