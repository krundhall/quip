#pragma once
#include "attributes.h"
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
    PlayerAttributes starting_attrs;
};

namespace PlayerConfigs
{
const PlayerConfig MAGE = {
    .health = 10,
    .speed = {300, 300},
    .size = {40, 75},
    .scale = 4.0f,
    .sprite_name = "player",
    .starting_attrs = {
        .strength = 1, .agility = 1, .intelligence = 5, .vitality = 10, .spirit = 15}};
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
