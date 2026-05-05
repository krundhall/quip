#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

struct Animation
{
    int row;
    int frame_count;
};

struct SpriteSheet
{
    Texture2D texture;
    int frame_width;
    int frame_height;
    std::unordered_map<std::string, Animation> animations;
};

struct TextureManager
{
    std::unordered_map<std::string, SpriteSheet> spritesheets;
};

void textures_init(TextureManager &manager);

SpriteSheet* textures_load(TextureManager &manager, const std::string &name,
                           const std::string &path, int frame_width, int frame_height);
void textures_add_animation(TextureManager &manager, const std::string &sheet_name,
                            const std::string &anim_name, int row, int frame_count);
void draw_sprite_animation(const SpriteSheet &sheet, const std::string &anim_name, int frame,
                           Vector2 position, float rotation = 0.0f, float scale = 1.0f,
                           bool flip_horizontal = false, Color tint = WHITE);
void textures_unload_all(TextureManager &manager);
SpriteSheet* textures_get(TextureManager &manager, const std::string &name);
void assets_init(TextureManager &manager);
