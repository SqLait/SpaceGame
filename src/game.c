
#include "game.h"
#include "raylib.h"

void load_assets() {
    Image img = LoadImage("assets/Shippy.png");
    ImageFlipVertical(&img);
    textures[0] = LoadTextureFromImage(img);
}
