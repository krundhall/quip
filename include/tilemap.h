#pragma once
#include <raylib.h>
#include <string>
#include <vector>

struct DrawableTile
{
    int tile_id;
    float world_x;
    float world_y;
};

struct TileSet
{
    int first_gid;
    std::string path;
    int columns;
    int tile_size;
    int tile_count;
    Texture2D texture;
};

struct TileMap
{
    int width;
    int height;
    int tile_size;
    std::vector<TileSet> tilesets;
    std::vector<Rectangle> collision_boxes;
    std::vector<std::vector<int>> ground_layers;
    std::vector<DrawableTile> object_tiles;
};


inline int get_index_for_tile(const std::vector<int> &layer, int width, int x, int y)
{
    // (x, y) = index % width
    return layer[width * y + x];
}
TileMap load_tilemap(const std::string &path);

void tilemap_draw_ground(const TileMap &map, int scale);
void tilemap_draw_object(const TileMap &map, int scale);
