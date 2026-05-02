#pragma once
#include "Ball.h"
#include "Player.h"

enum class GameState { SERVING, PLAYING };

struct GameWorld
{
    Player playerLeft = Player(PlayerSide::LEFT);
    Player playerRight = Player(PlayerSide::RIGHT);
    Ball ball;
    int scoreLeft = 0;
    int scoreRight = 0;
    GameState state = GameState::SERVING;
    PlayerSide server = PlayerSide::LEFT;
    void reset(PlayerSide scorer);
};

void player_ball_collisions(GameWorld &world);
