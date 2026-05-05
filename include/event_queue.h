#pragma once
#include "player.h"
#include <raylib.h>
#include <vector>

enum class EventType
{
    XP_GAINED,
    LEVEL_UP,
    PLAYER_DIED,
    PLAYER_HIT,
    ENEMY_HIT,
    ENEMY_DIED
};

struct HitData
{
    int damage;
    Vector2 position;
    Vector2 direction;
    Vector2 knockback;
};

union EventData
{
    int xp_amount;
    HitData hit;
};

struct Event
{
    EventType type;
    EventData data;
};

extern std::vector<Event> g_event_queue;
void process_events(Player &player, GAMESTATE &state);


inline Event make_xp_event(int amount)
{
    return Event{EventType::XP_GAINED, {.xp_amount = amount}};
}

inline Event make_level_up_event()
{
    return Event{EventType::LEVEL_UP, EventData{}};
}

inline Event make_player_died_event()
{
    return Event{EventType::PLAYER_DIED, EventData{}};
}

inline Event make_player_hit_event(int damage, Vector2 position)
{
    return Event{EventType::PLAYER_HIT, {.hit = {damage, position, {0, 0}, {0, 0}}}};
}

inline Event make_enemy_hit_event(int damage, Vector2 position, Vector2 direction,
                                  Vector2 knockback)
{
    return Event{EventType::ENEMY_HIT, {.hit = {damage, position, direction, knockback}}};
}

inline Event make_enemy_died_event()
{
    return Event{EventType::ENEMY_DIED, EventData{}};
}
