#include "events.h"

void enemy_on_death(Player &player, const Enemy &enemy)
{
    // XP
    player.xp += enemy.xp_dropped;
    // LOOT
}
