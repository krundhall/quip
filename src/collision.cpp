#include "collision.h"
#include "constants.h"
#include "event_queue.h"
#include "helper.h"
#include "raylib.h"
#include "raymath.h"
#include "tilemap.h"

void player_enemy_collision(Player &player, std::vector<Enemy> &enemies)
{
    if (player.health <= 0)
        return;

    for (auto &enemy : enemies)
    {
        if (!_aabb_rec(player.position, player.size, enemy.position, enemy.size))
            continue;

        if (player.hit_timer <= 0 && enemy.swing_timer <= 0)
        {
            g_event_queue.push_back(make_player_hit_event(enemy.damage, player.position));
            enemy.swing_timer = ENEMY_SWING_TIMER;
        }
    }
}


void enemy_enemy_collision(std::vector<Enemy> &enemies)
{
    for (size_t i = 0; i < enemies.size(); i++)
        for (size_t j = i + 1; j < enemies.size(); j++)
        {
            _aabb_rec(enemies[i].position, enemies[i].size, enemies[j].position, enemies[j].size);
        }
}


bool _aabb_rec(Vector2 &object1_position, const Vector2 &object1_size, Vector2 &object2_position,
               const Vector2 &object2_size)
{
    Rectangle object1_rectangle = {object1_position.x - (object1_size.x / 2),
                                   object1_position.y - (object1_size.y / 2),
                                   object1_size.x,
                                   object1_size.y};
    Rectangle object2_rectangle = {object2_position.x - (object2_size.x / 2),
                                   object2_position.y - (object2_size.y / 2),
                                   object2_size.x,
                                   object2_size.y};

    if (!CheckCollisionRecs(object1_rectangle, object2_rectangle))
        return false;

    Vector2 normal = Vector2Normalize(Vector2Subtract(object2_position, object1_position));

    auto x_overlap = std::min((object1_rectangle.x + object1_rectangle.width),
                              (object2_rectangle.x + object2_rectangle.width)) -
                     std::max(object1_rectangle.x, object2_rectangle.x);
    auto y_overlap = std::min((object1_rectangle.y + object1_rectangle.height),
                              (object2_rectangle.y + object2_rectangle.height)) -
                     std::max(object1_rectangle.y, object2_rectangle.y);

    if (x_overlap < y_overlap)
    {
        object1_position.x -= normal.x * x_overlap;
        object2_position.x += normal.x * x_overlap;
        return true;
    }
    else
    {
        object1_position.y -= normal.y * y_overlap;
        object2_position.y += normal.y * y_overlap;
        return true;
    }
}

void player_tilemap_collision(Player &player, const TileMap &map)
{
    Rectangle player_rect = {player.position.x - (player.size.x / 2),
                             player.position.y - (player.size.y / 2),
                             player.size.x,
                             player.size.y};

    for (const auto &box : map.collision_boxes)
    {
        if (!CheckCollisionRecs(player_rect, box))
            continue;

        Vector2 box_center = {box.x + box.width / 2, box.y + box.height / 2};
        Vector2 normal = Vector2Normalize(Vector2Subtract(box_center, player.position));

        auto x_overlap = std::min(player_rect.x + player_rect.width, box.x + box.width) -
                         std::max(player_rect.x, box.x);
        auto y_overlap = std::min(player_rect.y + player_rect.height, box.y + box.height) -
                         std::max(player_rect.y, box.y);

        if (x_overlap < y_overlap)
            player.position.x -= normal.x * x_overlap;
        else
            player.position.y -= normal.y * y_overlap;

        player_rect = {player.position.x - (player.size.x / 2),
                       player.position.y - (player.size.y / 2),
                       player.size.x,
                       player.size.y};
    }
}

void spell_collision(Player &player, std::vector<Enemy> &enemies, const TileMap &map)
{
    for (auto &enemy : enemies)
        for (int i = 0; i < player.spell_count; i++)
        {
            if (enemy.health <= 0)
                continue;

            if (!CheckCollisionCircleRec(player.spells[i].position,
                                         player.spells[i].radius,
                                         {enemy.position.x - (enemy.size.x / 2),
                                          enemy.position.y - (enemy.size.y / 2),
                                          enemy.size.x,
                                          enemy.size.y}))
            {
                continue;
            }

            Vector2 dir = Vector2Normalize(player.spells[i].velocity);
            enemy.health -= player.spells[i].damage;
            enemy.knockback_vel = Vector2Scale(dir, player.spells[i].knockback);
            enemy.hit_timer = 0.4f;
            enemy.anim.current_animation = EntityAnimation::HIT;
            enemy.anim.current_frame = 0;
            player.spells[i].alive = false;
        }

    for (const auto &box : map.collision_boxes)
        for (int i = 0; i < player.spell_count; i++)
        {
            if (!CheckCollisionCircleRec(
                    player.spells[i].position, player.spells[i].radius, (Rectangle)box))
                continue;

            player.spells[i].alive = false;
        }
}
