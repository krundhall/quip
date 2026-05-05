#pragma once
#include "player.h"
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
