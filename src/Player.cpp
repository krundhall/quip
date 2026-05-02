#include "Player.h"
#include "constants.h"

Player::Player(PlayerSide side)
    : speed(PLAYER_SPEED),
      side(side),
      radius(PLAYER_RADIUS)
{
    if (side == PlayerSide::LEFT)
    {
        position = {SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.75f};
        color = BLUE;
    }
    else
    {
        position = {SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.75f};
        color = RED;
    }
}

void Player::update(float dt)
{
    velocityY += GRAVITY * dt;
    position.y += velocityY * dt;

    if (position.y + radius >= SCREEN_HEIGHT)
    {
        position.y = SCREEN_HEIGHT - radius;
        velocityY = 0;
        jumpsLeft = 2;
    }
    if (position.y <= radius)
        position.y = radius;

    bool onGround = position.y + radius >= SCREEN_HEIGHT;

    if (side == PlayerSide::LEFT)
    {
        if (IsKeyPressed(KEY_W) && jumpsLeft > 0)
        {
            velocityY = JUMP_VELOCITY;
            jumpsLeft--;
        }
        if (IsKeyDown(KEY_S))
            velocityY += GRAVITY * dt;

        velocityX = 0;
        if (IsKeyDown(KEY_A)) velocityX = -speed;
        if (IsKeyDown(KEY_D)) velocityX =  speed;
        position.x += velocityX * dt;

        if (position.x - radius <= 0)
            position.x = radius;
        if (position.x + radius >= SCREEN_WIDTH / 2)
            position.x = SCREEN_WIDTH / 2 - radius;
    }
    else
    {
        if (IsKeyPressed(KEY_UP) && jumpsLeft > 0)
        {
            velocityY = JUMP_VELOCITY;
            jumpsLeft--;
        }
        if (IsKeyDown(KEY_DOWN))
            velocityY += GRAVITY * dt;

        velocityX = 0;
        if (IsKeyDown(KEY_LEFT))  velocityX = -speed;
        if (IsKeyDown(KEY_RIGHT)) velocityX =  speed;
        position.x += velocityX * dt;

        if (position.x - radius <= SCREEN_WIDTH / 2)
            position.x = SCREEN_WIDTH / 2 + radius;
        if (position.x + radius >= SCREEN_WIDTH)
            position.x = SCREEN_WIDTH - radius;
    }
}

void Player::draw()
{
    DrawCircleV(this->position, this->radius, this->color);
}
