#pragma once
#include "attributes.h"
#include "constants.h"
#include "enemy.h"
#include "entity_animation.h"
#include "enums.h"
#include "spells/spell.h"
#include <raylib.h>
#include <vector>

struct Player
{
    // Transform
    Vector2 position;
    Vector2 dir;
    Vector2 speed;
    Vector2 size;
    float scale;
    // Combat
    int health;
    float hit_timer;
    float death_timer;
    float swing_timer;
    // Progression
    int level;
    int xp;
    int attribute_points;
    int talent_points;
    PlayerAttributes attrs;
    PlayerStats stats;
    // Spells
    Spell spells[MAX_ACTIVE_SPELLS];
    int spell_count;
    // Rendering
    AnimationState anim;
    std::string sprite_name;
};

void player_update(Player &player, float dt, const Camera2D &camera);
void player_movement(Player &player, float dt);
void player_draw(Player &player, TextureManager &tex_manager);
void player_hud(const Player &player);
void player_cast(Player &player, const Camera2D &camera);
void player_animate(Player &player, float dt);
Player player_create(CLASSTYPE type, Vector2 position);
