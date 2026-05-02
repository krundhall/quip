#pragma once
#include <raylib.h>

enum class PlayerSide
{
    LEFT,
    RIGHT
};

class Player
{
public:
    float speed;
    float velocityX = 0;
    float velocityY = 0;
    int jumpsLeft = 2;
    Color color;
    PlayerSide side;
    Vector2 position;
    float radius;


    Player(PlayerSide side);
    void update(float dt);
    void draw();
};
