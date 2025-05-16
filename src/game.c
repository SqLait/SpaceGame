
#include "game.h"
#include "raylib.h"

void load_assets(Texture2D *textures) {
    Image ship = LoadImage("assets/Shippy.png");
    ImageFlipVertical(&ship);
    textures[0] = LoadTextureFromImage(ship);
    textures[1] = LoadTextureFromImage(LoadImage("assets/Star.png"));
}
