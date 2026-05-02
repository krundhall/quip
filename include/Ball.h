#pragma once
#include "Player.h"
#include <raylib.h>
#include <raymath.h>

class Ball
{
public:
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    PlayerSide start;

    int touchCount = 0;

    Ball();

    void update(float dt);
    void draw();
};
