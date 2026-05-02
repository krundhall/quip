#include "GameWorld.h"
#include "MenuScene.h"
#include "PlayingScene.h"
#include "constants.h"
#include <memory>
#include <raylib.h>

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ava");
    SetExitKey(KEY_NULL);
    SetTargetFPS(120);

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    GameWorld world;
    std::unique_ptr<Scene> scene = std::make_unique<MenuScene>(world);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_F))
            ToggleBorderlessWindowed();

        auto next = scene->update(dt);
        if (next)
            scene = std::move(next);

        BeginTextureMode(target);
        ClearBackground(GRAY);
        scene->draw();
        EndTextureMode();

        int winW = GetScreenWidth();
        int winH = GetScreenHeight();
        float scale = (winW / (float)SCREEN_WIDTH < winH / (float)SCREEN_HEIGHT)
                          ? winW / (float)SCREEN_WIDTH
                          : winH / (float)SCREEN_HEIGHT;

        float offsetX = (winW - SCREEN_WIDTH * scale) / 2.0f;
        float offsetY = (winH - SCREEN_HEIGHT * scale) / 2.0f;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(target.texture,
                       {0, 0, (float)SCREEN_WIDTH, -(float)SCREEN_HEIGHT},
                       {offsetX, offsetY, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale},
                       {0, 0},
                       0,
                       WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}
