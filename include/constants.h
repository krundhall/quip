#pragma once

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 1000;
// player
constexpr float PLAYER_RADIUS = 45.0f;
constexpr float PLAYER_SPEED = 500.0f;
constexpr float GRAVITY = 1750.0f;
constexpr float JUMP_VELOCITY = -1000.0f;

// ball
constexpr float BALL_RADIUS = 60.0f;
constexpr float BALL_INITIAL_SPEED = 150.0f;
constexpr float MAX_BALL_SPEED = 1200.0f;
constexpr int SPEED_UP_TOUCHES = 8;
constexpr float SPEED_UP_FACTOR = 1.3f;

// net
constexpr int NET_WIDTH = 4;
constexpr int NET_TOP = SCREEN_HEIGHT * 2 / 3;
constexpr int NET_X = SCREEN_WIDTH / 2 - NET_WIDTH / 2;
