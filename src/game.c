#include "game.h"
#include "objects.h"
#include "raylib.h"
#include "alloc.h"
#include "debug.h"
#include "dynlist.h"

Texture2D textures[2];
Pool* pool;
Object* bullets = NULL;
f32 time_passed = 2;

Game game = {
    .game_state = RUNNING,
    .update_game = true,
};

Object player = {
    .position = { (f32)G_WIDTH / 2, 900 },
    .texture_id = 0,
};

void init() {
    Image ship = LoadImage("assets/Shippy.png");
    ASSERT_MSG(ship.data != NULL, "Failed to load 'Shippy.png'");

    ImageFlipVertical(&ship);
    textures[0] = LoadTextureFromImage(ship);
    UnloadImage(ship);

    Image star = LoadImage("assets/Star.png");
    ASSERT_MSG(star.data != NULL, "Failed to load 'Star.png'");

    textures[1] = LoadTextureFromImage(star);
    UnloadImage(star);

    pool = pool_new(12);
    bullets = dynlist_init(Object);
}

void deinit() {
    pool_close(pool);
    dynlist_destroy(bullets);
}

void update() {
    time_passed += GetFrameTime();

    PlayerInput(&player);
    UpdateRect(&player.rect, &player.position, &textures[player.texture_id]);

    for (i32 i = dynlist_length(bullets) - 1; i >= 0; i--) {
        Object bullet = bullets[i];

        if (CheckBulletOutOfView(&bullets[i])) {
            dynlist_removeat(bullets, i);
            pool_free(pool, &bullet);
            continue; // Use continue to avoid use after free (UAF)
        }

        MoveBullet(&bullets[i], &textures[bullets[i].texture_id]);
    }

    if (IsKeyDown(KEY_SPACE) && time_passed >= 2) {
        time_passed = 0;
        Vector2 center = GetOrigin(&player.rect, &player.position);
        Object* bullet = CreateNewBullet(&center, &textures[1], pool);
        dynlist_push(bullets, *bullet);
    }
}

void draw() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(textures[player.texture_id], player.position.x, player.position.y, WHITE);
    DrawRectangleLines(player.rect.x, player.rect.y, player.rect.width, player.rect.height, RED);
    for (size i = 0; i < dynlist_length(bullets); i++) {
        DrawTexture(textures[bullets[i].texture_id], bullets[i].position.x, bullets[i].position.y, WHITE);
    }
    EndDrawing();
}
