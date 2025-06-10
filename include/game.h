#ifndef GAME_H
#define GAME_H
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
} Game;

void init();
void update();
void draw();
void deinit();
#endif
