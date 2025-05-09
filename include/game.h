#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include "types.h"
#define G_WIDTH 1080
#define G_HEIGHT 1920
enum GameState : u8 {
    RUNNING,
    PAUSE,
    END
};

typedef struct {
    enum GameState gameState;   
} Game;
#endif
