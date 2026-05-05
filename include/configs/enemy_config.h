#pragma once
#include "constants.h"
#include "enums.h"
#include <raylib.h>
#include <string>
struct EnemyConfig
{
    int health;
    Vector2 speed;
    Vector2 size;
    float aggro_radius;
    float damage;
    float scale;
    float swing_timer;
    std::string sprite_name;
    int xp_dropped;
    int level;
};

namespace EnemyConfigs
{
const EnemyConfig GOBLIN = {.health = 5,
                            .speed = {50, 50},
                            .size = {25, 45},
                            .aggro_radius = 400,
                            .damage = 1.0f,
                            .scale = 3.5f,
                            .swing_timer = ENEMY_SWING_TIMER,
                            .sprite_name = "enemy",
                            .xp_dropped = 5,
                            .level = 1};
};

inline const EnemyConfig* get_enemy_config(ENEMYTYPE type)
{
    switch (type)
    {
    case ENEMYTYPE::GOBLIN:
        return &EnemyConfigs::GOBLIN;
    }
    return nullptr;
}
