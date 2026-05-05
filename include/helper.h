#pragma once
#include "constants.h"
#include "player.h"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

inline Vector2 _rec_center(const Vector2 &position, const Vector2 &size)
{
    return {position.x + (size.x / 2), position.y + (size.y / 2)};
}

inline Vector2 _normal_from_mouse(const Player &player, const Camera2D &camera)
{
    return Vector2Normalize(
        Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), player.position));
}

inline int xp_to_next_level(int level)
{
    return (int)(50 * pow(level, 1.3f));
}
