#pragma once
#include "player.h"
#include <raylib.h>
#include <vector>

enum class EventType
{
    XP_GAINED,
    LEVEL_UP,
    PLAYER_DIED
};

union EventData
{
    int xp_amount;
    Vector2 position;
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
