#include "Ball.h"
#include "constants.h"

Ball::Ball()
    : position({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}),
      speed({BALL_INITIAL_SPEED, -BALL_INITIAL_SPEED * 2.4f}),
      radius(BALL_RADIUS),
      color(GREEN),
      start(PlayerSide::LEFT)
{
}

void Ball::update(float dt)
{
    speed.y += GRAVITY * dt;

    position.x += speed.x * dt;
    position.y += speed.y * dt;

    if (position.y - radius <= 0)
        speed.y *= -1;

    if (position.x - radius <= 0)
    {
        position.x = radius;
        speed.x *= -1;
    }
    if (position.x + radius >= SCREEN_WIDTH)
    {
        position.x = SCREEN_WIDTH - radius;
        speed.x *= -1;
    }
}

void Ball::draw()
{
    DrawCircleV(this->position, this->radius, this->color);
}
