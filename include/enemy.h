#pragma once
#include "entity_animation.h"
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
    Vector2 knockback_vel;

    AnimationState anim;

    Color color;
};

std::vector<Enemy> _build_enemy_array();
void enemy_update(const Player &player, std::vector<Enemy> &enemies, float dt);
void enemy_draw(std::vector<Enemy> &enemies, TextureManager &tex_manager);
Enemy enemy_init(Vector2 position);
