#include "GameWorld.h"
#include "constants.h"
#include <raymath.h>

void GameWorld::reset(PlayerSide scorer)
{
    server = (scorer == PlayerSide::LEFT) ? PlayerSide::RIGHT : PlayerSide::LEFT;
    state = GameState::SERVING;

    float ballX = (server == PlayerSide::LEFT) ? SCREEN_WIDTH * 0.35f : SCREEN_WIDTH * 0.65f;
    ball.position = {ballX, SCREEN_HEIGHT * 0.48f};
    ball.speed = {0, 0};
    ball.touchCount = 0;
}

static void resolve_collision(GameWorld &world, Player &player)
{
    Vector2 &ballPos = world.ball.position;
    Vector2 &ballVel = world.ball.speed;
    Vector2  playerVel = {player.velocityX, player.velocityY};

    Vector2 diff = {ballPos.x - player.position.x, ballPos.y - player.position.y};
    float dist = Vector2Length(diff);

    if (dist == 0)
        return;

    Vector2 normal = Vector2Scale(diff, 1.0f / dist);

    // push ball fully out of player + small epsilon
    float overlap = (world.ball.radius + player.radius) - dist;
    ballPos = Vector2Add(ballPos, Vector2Scale(normal, overlap + 1.0f));

    // only reflect if ball is approaching relative to player
    Vector2 relVel = Vector2Subtract(ballVel, playerVel);
    float dot = Vector2DotProduct(relVel, normal);
    if (dot >= 0)
        return;

    ballVel = Vector2Subtract(ballVel, Vector2Scale(normal, 2 * dot));

    world.ball.touchCount++;
    if (world.ball.touchCount % SPEED_UP_TOUCHES == 0)
        ballVel = Vector2Scale(ballVel, SPEED_UP_FACTOR);

    ballVel = Vector2ClampValue(ballVel, 0, MAX_BALL_SPEED);
}

void player_ball_collisions(GameWorld &world)
{
    if (CheckCollisionCircles(world.playerLeft.position, world.playerLeft.radius,
                              world.ball.position, world.ball.radius))
        resolve_collision(world, world.playerLeft);

    if (CheckCollisionCircles(world.playerRight.position, world.playerRight.radius,
                              world.ball.position, world.ball.radius))
        resolve_collision(world, world.playerRight);
}
