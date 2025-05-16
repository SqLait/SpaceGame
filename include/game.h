#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "types.h"
#include "objects.h"
#define G_WIDTH 1080
#define G_HEIGHT 1920
enum GameState : u8 {
    RUNNING,
    PAUSE,
    END
};

typedef struct {
    enum GameState game_state;   
    bool update_game;
    Object player;
    Object enemies[15];
    Object bullets[10];
} Game;

typedef struct {
    void *buffer;
} MemPool;

void load_assets(Texture2D *);
#endif
