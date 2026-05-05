#pragma once
#include "enums.h"
#include "texture_manager.h"
#include <raylib.h>

struct Spell
{
    SPELLTYPE type;
    Vector2 position;
    Vector2 velocity;
    float lifetime;
    bool alive;
    SPELLTAG tag;

    int damage;
    float radius;
    float knockback;

    // Animation
    int current_frame;
    float frame_timer;

    float rotation;
    float scale;
};

Spell spell_create(SPELLTYPE type, Vector2 position, Vector2 direction);
void spell_update(Spell* spell, float dt);
void spell_draw(const Spell* spell, TextureManager &tex_manager);
