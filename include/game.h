#ifndef GAME_H
#define GAME_H
#include "types.h"
#include <raylib.h>
#define G_WIDTH 1920
#define G_HEIGHT 1080 
enum GameState {
    RUNNING,
    PAUSE,
    END
};

typedef struct {
    enum GameState game_state;   
    bool update_game;
    f32 delta_time;
} Game;

void init(void);
void update(void);
void draw(void);
void deinit(void);
#endif
