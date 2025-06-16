#include "game.h"
#include "objects.h"
#include "raylib.h"
#include "alloc.h"
#include "debug.h"
#include "dynlist.h"
#include "time.h"

Texture2D textures[3];
Allocator bullet_pool;
Allocator enemy_pool;
Object **bullets = NULL;
Object **enemies = NULL;

f32 time_passed = 2;
f32 enemy_time_passed = 1.5;

Game game = {
    .game_state = RUNNING,
    .update_game = true,
    .delta_time = 0
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

    Image enemy_ship = LoadImage("assets/Shippy.png");
    ASSERT_MSG(enemy_ship.data != NULL, "Failed to load 'Shippy.png'");
    textures[2] = LoadTextureFromImage(enemy_ship);
    UnloadImage(enemy_ship);
    
    bullet_pool = pool_allocator(pool_new(12));
    enemy_pool = pool_allocator(pool_new(24));
    bullets = dynlist_init(Object *);
    enemies = dynlist_init(Object *);

    srand(time(NULL));
}

void deinit(void) {
    bullet_pool.close(&bullet_pool);
    enemy_pool.close(&enemy_pool);
    dynlist_destroy(bullets);
    dynlist_destroy(enemies);
}

void update(void) {
    time_passed += GetFrameTime();
    enemy_time_passed += GetFrameTime();

    PlayerInput(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);

    update_bullets(bullets, &textures[1], &bullet_pool);
    update_enemies(enemies, &textures[2], &enemy_pool);
    CheckBulletCollision(enemies, &enemy_pool, bullets, &bullet_pool);

    if (IsKeyDown(KEY_SPACE) && time_passed >= 1) {
        time_passed = 0;
        Vector2 center = GetOrigin(&player.rect, &player.position);
        Object *bullet = CreateNewBullet(&center, &textures[1], &bullet_pool);
        dynlist_push(bullets, bullet);
    }

    if (enemy_time_passed >= 1.5) {
        enemy_time_passed = 0;
        Vector2 spawn = {
            .x = new_random(G_WIDTH + 20),
            .y = 0
        };
        Object *enemy = CreateNewEnemy(&spawn, &textures[2], &enemy_pool);
        dynlist_push(enemies, enemy);
    }
}

void draw(void) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawTexture(textures[player.texture_id], player.position.x, player.position.y, WHITE);

    for (size i = 0; i < dynlist_length(bullets); i++) {
        DrawTexture(textures[bullets[i]->texture_id], bullets[i]->position.x, bullets[i]->position.y, WHITE);
    }
    for (size i = 0; i < dynlist_length(enemies); i++) {
        DrawTexture(textures[enemies[i]->texture_id], enemies[i]->position.x, enemies[i]->position.y, RED);
    }
    EndDrawing();
}
