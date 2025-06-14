#include "game.h"
#include "objects.h"
#include "raylib.h"
#include "alloc.h"
#include "debug.h"
#include "dynlist.h"
#include "time.h"
#include "dict.h"

Texture2D textures[2];
Allocator bullet_pool;
Object** bullets = NULL;
f32 time_passed = 2;

Game game = {
    .game_state = RUNNING,
    .update_game = true,
};

Object player = {
    .position = { (f32)G_WIDTH / 2, 900 },
    .texture_id = 0,
};

void init(void) {
    Image ship = LoadImage("assets/Shippy.png");
    ASSERT_MSG(ship.data != NULL, "Failed to load 'Shippy.png'");

    ImageFlipVertical(&ship);
    textures[0] = LoadTextureFromImage(ship);
    UnloadImage(ship);

    Image star = LoadImage("assets/Star.png");
    ASSERT_MSG(star.data != NULL, "Failed to load 'Star.png'");

    textures[1] = LoadTextureFromImage(star);
    UnloadImage(star);
    
    Pool *pool = pool_new(12);
    bullet_pool = pool_allocator(pool);
    bullets = dynlist_init(Object *);
    srand(time(NULL));
}

void deinit(void) {
    bullet_pool.close(&bullet_pool);
    dynlist_destroy(bullets);
}

void update(void) {
    time_passed += GetFrameTime();

    PlayerInput(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);

    update_bullets(bullets, &textures[1], &bullet_pool);

    if (IsKeyDown(KEY_SPACE) && time_passed >= 2) {
        time_passed = 0;
        Vector2 center = GetOrigin(&player.rect, &player.position);
        Object* bullet = CreateNewBullet(&center, &textures[1], &bullet_pool);
        dynlist_push(bullets, bullet);
    }

    if (time_passed >= 1.5) {

    }
}

void draw(void) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(textures[player.texture_id], player.position.x, player.position.y, WHITE);
    DrawRectangleLines(player.rect.x, player.rect.y, player.rect.width, player.rect.height, RED);
    for (size i = 0; i < dynlist_length(bullets); i++) {
        DrawTexture(textures[bullets[i]->texture_id], bullets[i]->position.x, bullets[i]->position.y, WHITE);
    }
    EndDrawing();
}
