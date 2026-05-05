#pragma once
#include "spell.h"
#include <string>
struct SpellConfig
{
    float speed;
    float lifetime;
    int damage;
    float scale;
    float radius;
    float knockback;
    SPELLTAG tag;
    std::string sprite_name;
    std::string animation_name;
};

namespace SpellConfigs
{
const SpellConfig FIREBALL = {.speed = 750.0f,
                              .lifetime = 5.0f,
                              .damage = 10,
                              .scale = 3.0f,
                              .radius = 18.0f,
                              .knockback = 1000.0f,
                              .tag = SPELLTAG::FIRE,
                              .sprite_name = "fireball",
                              .animation_name = "default"};

const SpellConfig TELEPORT = {.speed = 0.0f,
                              .lifetime = 0.5f,
                              .damage = 0,
                              .scale = 3.0f,
                              .radius = 0.0f,
                              .knockback = 1.0f,
                              .tag = SPELLTAG::ARCANE,
                              .sprite_name = "teleport",
                              .animation_name = "default"};

} // namespace SpellConfigs

inline const SpellConfig* get_spell_config(SPELLTYPE type)
{
    switch (type)
    {
    case SPELLTYPE::FIREBALL:
        return &SpellConfigs::FIREBALL;
    case SPELLTYPE::TELEPORT:
        return &SpellConfigs::TELEPORT;
    }
    return nullptr;
}
