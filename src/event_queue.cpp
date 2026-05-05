#include "event_queue.h"
#include "helper.h"

std::vector<Event> g_event_queue;

void process_events(Player &player, GAMESTATE &state)
{
    std::vector<Event> pending;
    for (auto &event : g_event_queue)
    {
        switch (event.type)
        {
        case EventType::XP_GAINED:
        {
            player.xp += event.data.xp_amount;
            if (player.xp > xp_to_next_level(player.level))
                pending.push_back(make_level_up_event());
            break;
        }
        case EventType::LEVEL_UP:
        {
            player.level++;
            player.attribute_points++;
            player.talent_points++;
            break;
        }
        case EventType::PLAYER_DIED:
        {
            state = GAMESTATE::GAMEOVER;
            break;
        }
        case EventType::PLAYER_HIT:
        {
            player.health -= event.data.hit.damage;
            if (player.health <= 0)
                pending.push_back(make_player_died_event());

            player.hit_timer = 0.25f;
            player.anim.current_animation = EntityAnimation::HIT;
            player.anim.current_frame = 0;
            break;
        }
        case EventType::ENEMY_DIED:
        {
            break;
        }
        }
    }
    g_event_queue.clear();
    g_event_queue.insert(g_event_queue.end(), pending.begin(), pending.end());
}
