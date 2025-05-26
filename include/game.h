#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "poolalloc.h"
#include "types.h"
#include "objects.h"
#define G_WIDTH 1920
#define G_HEIGHT 1080 
enum GameState : u8 {
    RUNNING,
    PAUSE,
    END
};

typedef struct {
    enum GameState game_state;   
    bool update_game;
    Object player;
    Object *enemies;
    Object *bullets;
} Game;

void init();
void update();
void draw();
#endif
