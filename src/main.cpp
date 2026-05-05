/*
GODOT IS GAY
REJECT CONFORMITY
EMBRACE CHALLENGE
DONT BE AFRAID TO FAIL
*/

#include "camera.h"
#include "collision.h"
#include "constants.h"
#include "enemy.h"
#include "enums.h"
#include "event_queue.h"
#include "helper.h"
#include "player.h"
#include "spells/spell.h"
#include "texture_manager.h"
#include <raylib.h>

void update(Player &player, std::vector<Enemy> &enemies, Camera2D &camera, float dt);
void draw(Player &player, std::vector<Enemy> &enemies, Camera2D &camera,
          TextureManager &tex_manager);
void window_init();
auto state = GAMESTATE::MAINMENU;
int main()
{
    window_init();
    Player player =
        player_create(CLASSTYPE::MAGE, {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2});
    Camera2D camera = camera_init(player);
    auto enemies = _build_enemy_array();
    TextureManager tex_manager;
    textures_init(tex_manager);
    assets_init(tex_manager);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        switch (state)
        {
        case GAMESTATE::MAINMENU:
        {
            DrawText("Enter to play", GetScreenWidth() / 2, GetScreenHeight() / 2, 20, RAYWHITE);
            if (IsKeyPressed(KEY_ENTER))
                state = GAMESTATE::PLAYING;
            break;
        }
        case GAMESTATE::PLAYING:
        {
            BeginMode2D(camera);

            update(player, enemies, camera, dt);
            process_events(player, state);
            draw(player, enemies, camera, tex_manager);

            EndMode2D();
            break;
        }
        case GAMESTATE::GAMEOVER:
        {
            DrawText("Game Over", GetScreenWidth() / 2, GetScreenHeight() / 2, 20, RAYWHITE);
            DrawText("Press R to restart",
                     GetScreenWidth() / 2,
                     GetScreenHeight() / 2 + 50,
                     20,
                     RAYWHITE);
            if (IsKeyPressed(KEY_R))
            {
                player = player_create(CLASSTYPE::MAGE,
                                       {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2});
                enemies = _build_enemy_array();
                state = GAMESTATE::PLAYING;
            }
            break;
        }
        }
        player_hud(player);
        DrawFPS(20, 20);
        EndDrawing();
    }
    textures_unload_all(tex_manager);
    CloseWindow();
    return 0;
}

void update(Player &player, std::vector<Enemy> &enemies, Camera2D &camera, float dt)
{
    player_update(player, dt, camera);
    enemy_update(player, enemies, dt);
    enemy_enemy_collision(enemies);
    player_enemy_collision(player, enemies);
    spell_collision(player, enemies);
    camera.target = Vector2{_rec_center(player.position, player.size)};
}

void draw(Player &player, std::vector<Enemy> &enemies, Camera2D & /*camera*/,
          TextureManager &tex_manager)
{
    player_draw(player, tex_manager);
    enemy_draw(enemies, tex_manager);

    for (int i = 0; i < player.spell_count; i++)
        spell_draw(&player.spells[i], tex_manager);
}

void window_init()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(120);
    ChangeDirectory(GetApplicationDirectory());
    InitWindow(800, 600, "Lol");

    int primary = 0;
    for (int i = 0; i < GetMonitorCount(); i++)
    {
        Vector2 pos = GetMonitorPosition(i);
        TraceLog(LOG_INFO,
                 "Monitor %d: pos=(%.0f, %.0f) size=%dx%d",
                 i,
                 pos.x,
                 pos.y,
                 GetMonitorWidth(i),
                 GetMonitorHeight(i));
        if (pos.x == 0 && pos.y == 0)
        {
            primary = i;
            break;
        }
    }

    Vector2 monPos = GetMonitorPosition(primary);
    SetWindowSize(GetMonitorWidth(primary), GetMonitorHeight(primary));
    SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    SetWindowPosition((int)monPos.x, (int)monPos.y);
}
