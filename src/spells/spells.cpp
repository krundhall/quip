#include "spells/spell.h"
#include "spells/spell_config.h"
#include "texture_manager.h"
#include <cmath>
#include <exception>
Spell spell_create(SPELLTYPE type, Vector2 position, Vector2 direction)
{
    const SpellConfig* config = get_spell_config(type);
    if (!config)
        return Spell{};

    Spell spell = {};
    spell.type = type;
    spell.position = position, spell.velocity.x = direction.x * config->speed;
    spell.velocity.y = direction.y * config->speed;
    spell.lifetime = config->lifetime;
    spell.damage = config->damage;
    spell.scale = config->scale;
    spell.tag = config->tag;
    spell.alive = true;
    spell.current_frame = 0;
    spell.frame_timer = 0.0f;
    spell.rotation = atan2f(direction.y, direction.x) * RAD2DEG;
    spell.radius = config->radius;
    spell.knockback = config->knockback;

    return spell;
}

void spell_update(Spell* spell, float dt)
{
    // Tick down lifetime
    spell->lifetime -= dt;

    spell->frame_timer += dt;
    if (spell->frame_timer >= 0.1f)
    {
        spell->frame_timer = 0.0f;
        spell->current_frame++; // used for modulo wrapping of spritesheet
    }


    switch (spell->type)
    {
    case SPELLTYPE::FIREBALL:
        // Move
        spell->position.x += spell->velocity.x * dt;
        spell->position.y += spell->velocity.y * dt;
        break;

    case SPELLTYPE::TELEPORT:
        // Idk mr.compilor
        break;
    }

    if (spell->lifetime <= 0)
        spell->alive = false;
}

void spell_draw(const Spell* spell, TextureManager &tex_manager)
{
    if (!spell->alive)
        return;

    const SpellConfig* config = get_spell_config(spell->type);
    if (!config)
        return;

    SpriteSheet* sheet = textures_get(tex_manager, config->sprite_name);
    if (sheet)
    {
        draw_sprite_animation(*sheet,
                              config->animation_name,
                              spell->current_frame,
                              spell->position,
                              spell->rotation,
                              spell->scale);
    }
}
