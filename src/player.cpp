#include "player.h"
#include "constants.h"
#include "entity_animation.h"
#include "helper.h"
#include "spells/spell.h"
#include <raymath.h>
#include <string>

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

void player_update(Player &player, float dt, const Camera2D &camera)
{
    player_movement(player, dt);
    player_cast(player, camera);
    entity_animate(player.anim, dt);

    if (player.hit_timer > 0)
        player.hit_timer--;

    // Update spells
    for (int i = 0; i < player.spell_count; i++)
        spell_update(&player.spells[i], dt);

    // Remove dead spells (array compacting)
    int write_index = 0;
    for (int read_index = 0; read_index < player.spell_count; read_index++)
    {
        if (player.spells[read_index].alive)
        {
            if (write_index != read_index)
                player.spells[write_index] = player.spells[read_index];
            write_index++;
        }
    }
    player.spell_count = write_index;
}

void player_movement(Player &player, float dt)
{
    Vector2 dir = {0, 0};
    if (IsKeyDown(KEY_W))
        dir.y -= 1;
    if (IsKeyDown(KEY_S))
        dir.y += 1;
    if (IsKeyDown(KEY_A))
        dir.x -= 1;
    if (IsKeyDown(KEY_D))
        dir.x += 1;
    // Not moving
    if (dir.x == 0 && dir.y == 0)
    {
        if (player.anim.current_animation != EntityAnimation::IDLE)
        {
            player.anim.current_animation = EntityAnimation::IDLE;
            player.anim.current_frame = 0;
        }
        return;
    }

    // Hauling ass
    if (player.anim.current_animation != EntityAnimation::RUNNING)
    {
        player.anim.current_animation = EntityAnimation::RUNNING;
        player.anim.current_frame = 0;
    }

    // Flip
    if (dir.x < 0)
        player.anim.flip_horizontal = true; // Moving left
    else if (dir.x > 0)
        player.anim.flip_horizontal = false; // Moving right


    player.position += Vector2Normalize(dir) * dt * player.speed;
}

void player_cast(Player &player, const Camera2D &camera)
{
    if (player.spell_count >= MAX_ACTIVE_SPELLS)
        return;

    if (IsKeyPressed(KEY_Q)) // FIREBALL
    {
        Vector2 normal = _normal_from_mouse(player, camera);
        Vector2 spawn_pos = {player.position.x, player.position.y + 25};
        // Offset so fireball spawns at the hands

        player.spells[player.spell_count] = spell_create(SPELLTYPE::FIREBALL, spawn_pos, normal);
        player.spell_count++;

        TraceLog(LOG_INFO, "Fireball created! Count: %d", player.spell_count); // $DEBUG
    }

    if (IsKeyPressed(KEY_E)) // TELEPORT
    {
        Vector2 destination = GetScreenToWorld2D(GetMousePosition(), camera);
        player.position = destination;

        Vector2 effect_position = {player.position.x - 2.0f, player.position.y + 25.0f};

        player.spells[player.spell_count] =
            spell_create(SPELLTYPE::TELEPORT, effect_position, {0, 0});
        player.spell_count++;
    }
}

void player_animate(Player &player, float dt)
{
    player.anim.frame_timer += dt;

    if (player.anim.frame_timer >= 0.1f)
    {
        player.anim.frame_timer = 0.0f;
        player.anim.current_frame++;
    }
}

void player_draw(Player &player, TextureManager &tex_manager)
{
    SpriteSheet* sheet = textures_get(tex_manager, "player");
    if (sheet)
    {
        std::string anim_name = animation_to_string(player.anim.current_animation);
        draw_sprite_animation(*sheet,
                              anim_name,
                              player.anim.current_frame,
                              player.position,
                              0.0f,
                              player.scale,
                              player.anim.flip_horizontal,
                              WHITE);
    }
    DrawRectangleLinesEx({player.position.x - (player.size.x / 2),
                          player.position.y - (player.size.y / 2) + 10.0f,
                          player.size.x,
                          player.size.y},
                         1,
                         GREEN);             // $DEBUG           // $DEBUG
    DrawCircleV(player.position, 3, YELLOW); // $DEBUG
}

void player_hud(const Player &player)
{
    float start_x = (GetScreenWidth() / 2) - ((PLAYER_HEALTH * (SQ_SIZE_X + GAP) - 2) / 2);
    for (int i = 0; i < player.health; i++)
    {
        DrawRectangleV(
            {start_x + i * (SQ_SIZE_X + GAP), HEALTH_BAR_Y}, {SQ_SIZE_X, SQ_SIZE_Y}, RED);
    }

    std::string coords;
    coords += "x: " + std::to_string((int)player.position.x);
    coords += "\ny: ";
    coords += std::to_string((int)player.position.y);
    DrawText(coords.c_str(), 20, 50, 20, RAYWHITE);
}



Player player_init()
{
    Player player;
    player.position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    player.speed = {300, 300};
    player.size = {40, 75};
    player.health = 10;
    player.hit_timer = 100;
    player.spell_count = 0;
    player.scale = 4.0f;

    player.anim.current_animation = EntityAnimation::IDLE;
    player.anim.current_frame = 0;
    player.anim.frame_timer = 0.0f;
    player.anim.flip_horizontal = false;

    return player;
}
