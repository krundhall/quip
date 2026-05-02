#include "PlayingScene.h"
#include "PausedScene.h"
#include "constants.h"
#include <raylib.h>
#include <string>

PlayingScene::PlayingScene(GameWorld &world)
    : world(world)
{
}

std::unique_ptr<Scene> PlayingScene::update(float dt)
{
    world.playerLeft.update(dt);
    world.playerRight.update(dt);

    Ball &ball = world.ball;

    if (world.state == GameState::SERVING)
    {
        Player &server = (world.server == PlayerSide::LEFT) ? world.playerLeft : world.playerRight;
        if (CheckCollisionCircles(server.position, server.radius, ball.position, ball.radius))
        {
            world.state = GameState::PLAYING;
            player_ball_collisions(world);
        }
    }
    else
    {
        ball.update(dt);
        player_ball_collisions(world);

        Rectangle net = {(float)NET_X, (float)NET_TOP, (float)NET_WIDTH, (float)(SCREEN_HEIGHT - NET_TOP)};
        if (CheckCollisionCircleRec(ball.position, ball.radius, net))
        {
            if (ball.position.x < NET_X)
                ball.position.x = NET_X - ball.radius;
            else
                ball.position.x = NET_X + NET_WIDTH + ball.radius;
            ball.speed.x *= -1;
        }

        if (ball.position.y + ball.radius >= SCREEN_HEIGHT)
        {
            if (ball.position.x < SCREEN_WIDTH / 2)
                world.scoreRight++;
            else
                world.scoreLeft++;
            world.reset(ball.position.x < SCREEN_WIDTH / 2 ? PlayerSide::RIGHT : PlayerSide::LEFT);
        }
    }

    if (IsKeyPressed(KEY_ESCAPE))
        return std::make_unique<PausedScene>(world);

    return nullptr;
}

void PlayingScene::draw()
{
    DrawRectangle(NET_X, NET_TOP, NET_WIDTH, SCREEN_HEIGHT - NET_TOP, WHITE);

    constexpr int fontSize = 40;
    std::string leftScore  = std::to_string(world.scoreLeft);
    std::string rightScore = std::to_string(world.scoreRight);

    DrawText(leftScore.c_str(),  SCREEN_WIDTH / 4     - MeasureText(leftScore.c_str(),  fontSize) / 2, 20, fontSize, WHITE);
    DrawText(rightScore.c_str(), SCREEN_WIDTH * 3 / 4 - MeasureText(rightScore.c_str(), fontSize) / 2, 20, fontSize, WHITE);

    world.playerLeft.draw();
    world.playerRight.draw();
    world.ball.draw();

    DrawFPS(10, 10);
}
