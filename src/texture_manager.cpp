#include "texture_manager.h"

void textures_init(TextureManager &manager)
{
    manager.spritesheets.clear();
}

SpriteSheet* textures_load(TextureManager &manager, const std::string &name,
                           const std::string &path, int frame_width, int frame_height)
{
    // Check if already loaded
    if (manager.spritesheets.find(name) != manager.spritesheets.end())
        return &manager.spritesheets[name];

    // Load new sheet
    SpriteSheet sheet;
    sheet.texture = LoadTexture(path.c_str());
    sheet.frame_width = frame_width;
    sheet.frame_height = frame_height;

    manager.spritesheets[name] = sheet;
    return &manager.spritesheets[name];
}

void textures_add_animation(TextureManager &manager, const std::string &sheet_name,
                            const std::string &anim_name, int row, int frame_count)
{
    auto it = manager.spritesheets.find(sheet_name);
    if (it != manager.spritesheets.end())
    {
        Animation anim;
        anim.row = row;
        anim.frame_count = frame_count;
        it->second.animations[anim_name] = anim;
    }
}

void draw_sprite_animation(const SpriteSheet &sheet, const std::string &anim_name, int frame,
                           Vector2 position, float rotation, float scale, bool flip_horizontal,
                           Color tint)
{
    // Find animation
    auto it = sheet.animations.find(anim_name);
    if (it == sheet.animations.end())
        return;

    const Animation &anim = it->second;

    // Clamp to anims frame count
    frame = frame % anim.frame_count;

    // src rect
    Rectangle source = {(float)(frame * sheet.frame_width),
                        (float)(anim.row * sheet.frame_height),
                        (float)sheet.frame_width * (flip_horizontal ? -1.0f : 1.0f),
                        (float)sheet.frame_height};
    Rectangle dest = {position.x,
                      position.y,
                      (float)sheet.frame_width * scale,
                      (float)sheet.frame_height * scale};
    Vector2 origin = {(float)sheet.frame_width * scale / 2.0f,
                      (float)sheet.frame_height * scale / 2.0f};

    DrawTexturePro(sheet.texture, source, dest, origin, rotation, tint);
}

void textures_unload_all(TextureManager &manager)
{
    for (auto &pair : manager.spritesheets)
        UnloadTexture(pair.second.texture);

    manager.spritesheets.clear();
}

SpriteSheet* textures_get(TextureManager &manager, const std::string &name)
{
    auto it = manager.spritesheets.find(name);
    if (it != manager.spritesheets.end())
        return &it->second;

    return nullptr;
}

void assets_init(TextureManager &manager)
{
    /* MANUAL LOADING CAUSE I HATE MY LIFE */

    // FIREBALL
    textures_load(manager, "fireball", "../assets/sprites/spells/FIREBALL_SPELL.png", 32, 32);
    textures_add_animation(manager, "fireball", "default", 0, 4);

    // TELEPORT
    textures_load(manager, "teleport", "../assets/sprites/spells/TELEPORT_SPELL.png", 32, 32);
    textures_add_animation(manager, "teleport", "default", 0, 4);

    // PLAYER, CORNELIUS
    textures_load(manager, "player", "../assets/sprites/player/CORNELIUS.png", 32, 32);
    textures_add_animation(manager, "player", "idle", 0, 8);
    textures_add_animation(manager, "player", "running", 1, 8);
    textures_add_animation(manager, "player", "hit", 2, 4);
    textures_add_animation(manager, "player", "death", 3, 4);

    // ENEMY
    textures_load(manager, "enemy", "../assets/sprites/enemies/GOBLIN.png", 32, 32);
    textures_add_animation(manager, "enemy", "idle", 0, 8);
    textures_add_animation(manager, "enemy", "running", 1, 8);
    textures_add_animation(manager, "enemy", "hit", 2, 4);
    textures_add_animation(manager, "enemy", "death", 3, 16);
}
