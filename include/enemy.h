#pragma once
#include "entity_animation.h"
#include "enums.h"
#include "texture_manager.h"
#include <raylib.h>
#include <vector>

struct Player; // forward

struct Enemy
{
    // Transform
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    float scale;
    // Combat
    int health;
    float hit_timer;
    float death_timer;
    float swing_timer;
    float damage;
    int level;
    Vector2 knockback_vel;
    // Progression
    int xp_dropped;
    // AI
    float aggro_radius;
    bool is_aggroed;
    // Rendering
    AnimationState anim;
    std::string sprite_name;
    Color color;
};
std::vector<Enemy> _build_enemy_array();
void enemy_update(Player &player, std::vector<Enemy> &enemies, float dt);
void enemy_draw(std::vector<Enemy> &enemies, TextureManager &tex_manager);
void enemy_draw_single(Enemy &enemy, TextureManager &tex_manager);
Enemy enemy_create(ENEMYTYPE type, Vector2 position);
