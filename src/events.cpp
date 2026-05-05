#include "events.h"
#include "event_queue.h"

void enemy_on_death(const Enemy &enemy)
{
    g_event_queue.push_back(make_xp_event(enemy.xp_dropped));
}

void player_on_levelup()
{
    g_event_queue.push_back(make_level_up_event());
}
