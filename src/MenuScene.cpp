#include "MenuScene.h"
#include "PlayingScene.h"
#include "constants.h"
#include <raylib.h>

MenuScene::MenuScene(GameWorld &world)
    : world(world)
{
}

std::unique_ptr<Scene> MenuScene::update(float /*dt*/)
{
    if (IsKeyPressed(KEY_ENTER))
        return std::make_unique<PlayingScene>(world);

    return nullptr;
}

void MenuScene::draw()
{
    constexpr int titleSize  = 80;
    constexpr int promptSize = 30;
    const char* title  = "BallBeach";
    const char* prompt = "Press ENTER to play";

    DrawText(title,  SCREEN_WIDTH / 2 - MeasureText(title,  titleSize)  / 2, SCREEN_HEIGHT / 2 - 80, titleSize,  RAYWHITE);
    DrawText(prompt, SCREEN_WIDTH / 2 - MeasureText(prompt, promptSize) / 2, SCREEN_HEIGHT / 2 + 40, promptSize, RAYWHITE);
}
