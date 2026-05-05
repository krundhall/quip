#pragma once
#include "entity_animation.h"
#include "enums.h"
#include "texture_manager.h"
#include <raylib.h>
#include <vector>

struct Player; // forward

struct Enemy
{
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    int health = 5;
    float aggro_radius = 400;
    bool is_aggroed = false;
    float scale;
    float hit_timer;
    float death_timer;
    float swing_timer;
    float damage;
    Vector2 knockback_vel;

    AnimationState anim;
    std::string sprite_name;
    Color color;
};

std::vector<Enemy> _build_enemy_array();
void enemy_update(const Player &player, std::vector<Enemy> &enemies, float dt);
void enemy_draw(std::vector<Enemy> &enemies, TextureManager &tex_manager);
Enemy enemy_create(ENEMYTYPE type, Vector2 position);
