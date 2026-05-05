#pragma once
#include "enums.h"
#include <raylib.h>
#include <string>
struct PlayerConfig
{
    int health;
    Vector2 speed;
    Vector2 size;
    float scale;
    std::string sprite_name;
    // SPELLTYPE start_spell, an endeavor for later
};

namespace PlayerConfigs
{
const PlayerConfig MAGE = {
    .health = 10, .speed = {300, 300}, .size = {40, 75}, .scale = 4.0f, .sprite_name = "player"};
};

inline const PlayerConfig* get_player_config(CLASSTYPE type)
{
    switch (type)
    {
    case CLASSTYPE::MAGE:
        return &PlayerConfigs::MAGE;
    }
    return nullptr;
}
