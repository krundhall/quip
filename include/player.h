#pragma once
#include "constants.h"
#include "enemy.h"
#include "entity_animation.h"
#include "enums.h"
#include "spells/spell.h"
#include <raylib.h>
#include <vector>

struct Player
{
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    int health;
    float hit_timer;
    float scale;
    Vector2 dir;
    float death_timer;
    Spell spells[MAX_ACTIVE_SPELLS];
    int spell_count;

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
