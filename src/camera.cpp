#include "camera.h"
#include "player.h"
#include <raylib.h>



Camera2D camera_init(const Player &player)
{
    Camera2D camera = {};
    camera.target = Vector2{player.position.x + 20.0f, player.position.y + 20.0f};
    camera.offset = Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    return camera;
}
