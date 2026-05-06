#pragma once
#include "enemy.h"
#include "player.h"
#include "tilemap.h"

bool _aabb_rec(Vector2 &object1_position, const Vector2 &object1_size, Vector2 &object2_position,
               const Vector2 &object2_size);
void player_tilemap_collision(Player &player, const TileMap &map);
void enemy_enemy_collision(std::vector<Enemy> &enemies);
void player_enemy_collision(Player &player, std::vector<Enemy> &enemies);
void spell_collision(Player &player, std::vector<Enemy> &enemies, const TileMap &map);
