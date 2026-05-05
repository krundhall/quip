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
#include "helper.h"
#include "player.h"
#include "spells/spell.h"
#include "texture_manager.h"
#include <raylib.h>


void update(Player &player, std::vector<Enemy> &enemies, Camera2D &camera, float dt);
void draw(Player &player, std::vector<Enemy> &enemies, Camera2D &camera,
          TextureManager &tex_manager);
void window_init();

int main()
{
    TraceLog(LOG_INFO, "WD: %s", GetWorkingDirectory());

    window_init();

    Player player = player_init();
    Camera2D camera = camera_init(player);
    auto enemies = _build_enemy_array();

    TextureManager tex_manager;
    textures_init(tex_manager);
    assets_init(tex_manager);


    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        update(player, enemies, camera, dt);
        draw(player, enemies, camera, tex_manager);
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

void draw(Player &player, std::vector<Enemy> &enemies, Camera2D &camera,
          TextureManager &tex_manager)
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);

    player_draw(player, tex_manager);
    enemy_draw(enemies, tex_manager);

    for (int i = 0; i < player.spell_count; i++)
        spell_draw(&player.spells[i], tex_manager);


    EndMode2D();
    player_hud(player);
    DrawFPS(20, 20);
    EndDrawing();
}

void window_init()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    SetTargetFPS(120);
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
