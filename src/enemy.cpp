#include "enemy.h"
#include "constants.h"
#include "helper.h"
#include "player.h"
#include <raymath.h>
#include <vector>

static std::string animation_to_string(EntityAnimation anim)
{
    switch (anim)
    {
    case EntityAnimation::IDLE:
        return "idle";
    case EntityAnimation::RUNNING:
        return "running";
    case EntityAnimation::HIT:
        return "hit";
    case EntityAnimation::DEATH:
        return "death";
    }
    return "idle";
}

std::vector<Enemy> _build_enemy_array()
{
    std::vector<Enemy> enemies;

    enemies.push_back(enemy_init({50, 100}));
    enemies.push_back(enemy_init({50, 250}));
    enemies.push_back(enemy_init({50, 500}));

    return enemies;
}

void enemy_update(const Player &player, std::vector<Enemy> &enemies, float dt)
{
    for (auto &enemy : enemies)
    {
        if (enemy.hit_timer > 0)
            enemy.hit_timer -= dt;
        if (enemy.hit_timer <= 0)
        {
            auto temp = enemy.anim.current_animation;
            enemy.anim.current_animation =
                (enemy.is_aggroed == true) ? EntityAnimation::RUNNING : EntityAnimation::IDLE;
            if (enemy.anim.current_animation != temp)
                enemy.anim.current_frame = 0;
        }

        Vector2 player_center = _rec_center(player.position, player.size);
        Vector2 enemy_center = _rec_center(enemy.position, enemy.size);

        Vector2 dir = Vector2Subtract(player_center, enemy_center);
        Vector2 normal = Vector2Normalize(dir);

        if (Vector2Distance(player_center, enemy_center) < enemy.aggro_radius || enemy.is_aggroed)
        {
            enemy.is_aggroed = true;
            enemy.position += enemy.speed * dt * normal;
        }

        if (Vector2Length(enemy.knockback_vel) > 0.5f)
        {
            enemy.position = Vector2Add(enemy.position, Vector2Scale(enemy.knockback_vel, dt));
            enemy.knockback_vel = Vector2Scale(enemy.knockback_vel, FRICTION);
        }
        entity_animate(enemy.anim, dt);
    }
    // Remove dead
    enemies.erase(std::remove_if(enemies.begin(),
                                 enemies.end(),
                                 [](const auto &enemy) { return enemy.health <= 0; }),
                  enemies.end());
}

void enemy_draw(std::vector<Enemy> &enemies, TextureManager &tex_manager)
{
    for (auto &enemy : enemies)
    {
        SpriteSheet* sheet = textures_get(tex_manager, "enemy");
        if (sheet)
        {
            std::string anim_name = animation_to_string(enemy.anim.current_animation);
            draw_sprite_animation(*sheet,
                                  anim_name,
                                  enemy.anim.current_frame,
                                  enemy.position,
                                  0.0f,
                                  enemy.scale,
                                  enemy.anim.flip_horizontal,
                                  WHITE);
        }
        DrawRectangleLinesEx({enemy.position.x - (enemy.size.x / 2),
                              enemy.position.y - (enemy.size.y / 2) + 10.0f,
                              enemy.size.x,
                              enemy.size.y},
                             1,
                             RED); // $DEBUG
    }
}

Enemy enemy_init(Vector2 position)
{
    Enemy enemy;
    enemy.position = position;
    enemy.speed = {50, 50};
    enemy.size = {25, 45};
    enemy.health = 5;
    enemy.aggro_radius = 400;
    enemy.is_aggroed = false;
    enemy.scale = 3.5f;
    enemy.hit_timer = 0.0f;
    enemy.knockback_vel = {0, 0};
    enemy.anim.current_animation = EntityAnimation::IDLE;
    enemy.anim.current_frame = 0;
    enemy.anim.frame_timer = 0.0f;
    enemy.anim.flip_horizontal = false;

    return enemy;
}
