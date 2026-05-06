#include "tilemap.h"
#include "enemy.h"
#include "player.h"
#include "texture_manager.h"
#include <algorithm>
#include <filesystem>
#include <iostream> // $DEBUG
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
TileMap load_tilemap(const std::string &path)
{
    TileMap result;

    tmx::Map map;
    map.load(path);

    result.width = map.getTileCount().x;
    result.height = map.getTileCount().y;
    result.tile_size = map.getTileSize().x;
    const auto &layers = map.getLayers();
    for (const auto &layer : layers)
    {
        if (layer->getType() == tmx::Layer::Type::Tile && layer->getName().substr(0, 2) == "A_")
        {
            const auto &tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto &tiles = tileLayer.getTiles();
            for (size_t i = 0; i < tiles.size(); i++)
            {
                if (tiles[i].ID == 0)
                    continue;

                DrawableTile dt;
                dt.tile_id = tiles[i].ID;
                dt.world_x = (i % result.width) * result.tile_size;
                dt.world_y = (i / result.width) * result.tile_size;
                result.object_tiles.push_back(dt);
            }
        }

        else if (layer->getType() == tmx::Layer::Type::Tile &&
                 layer->getName().substr(0, 2) == "G_")
        {
            std::vector<int> temp;
            std::cout << layer->getName() << '\n';
            const auto &tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto &tiles = tileLayer.getTiles();
            for (auto &t : tiles)
                temp.push_back(t.ID);

            result.ground_layers.push_back(temp);
        }

        else if (layer->getType() == tmx::Layer::Type::Object)
        {
            std::cout << layer->getName() << '\n';
            const auto &objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
            const auto boxes = objectLayer.getObjects();
            for (auto &b : boxes)
            {
                result.collision_boxes.push_back({
                    b.getPosition().x * 2,
                    b.getPosition().y * 2,
                    b.getAABB().width * 2,
                    b.getAABB().height * 2,
                });
            }
        }
    }

    const auto &tilesets = map.getTilesets();
    for (const auto &tileset : tilesets)
    {
        TileSet ts;
        ts.first_gid = tileset.getFirstGID();
        ts.path = tileset.getImagePath();
        ts.columns = tileset.getColumnCount();
        ts.tile_size = tileset.getTileSize().x;
        ts.tile_count = tileset.getTileCount();
        ts.texture = LoadTexture((ts.path).c_str());
        result.tilesets.push_back(ts);

        std::cout << ts.path << '\n'; // $DEBUG
    }

    return result;
}

void tilemap_draw_ground(const TileMap &map, int scale)
{
    for (const auto &layer : map.ground_layers)
    {
        for (size_t i = 0; i < layer.size(); i++)
        {
            float x, y;
            x = i % map.width;
            y = i / map.width;
            x *= map.tile_size;
            y *= map.tile_size;
            Rectangle destination = {
                x * scale, y * scale, (float)map.tile_size * scale, (float)map.tile_size * scale};

            for (const auto &tileset : map.tilesets)
            {
                // DrawRectangleRec(destination, RED);
                if (layer[i] >= tileset.first_gid &&
                    layer[i] < tileset.first_gid + tileset.tile_count)
                {
                    int local_id = layer[i] - tileset.first_gid;
                    int col = local_id % tileset.columns;
                    int row = local_id / tileset.columns;
                    int src_x = col * tileset.tile_size;
                    int src_y = row * tileset.tile_size;

                    Rectangle src = {(float)src_x,
                                     (float)src_y,
                                     (float)tileset.tile_size,
                                     (float)tileset.tile_size};

                    DrawTexturePro(tileset.texture, src, destination, {0, 0}, 0, WHITE);
                }
            }
        }
    }
}

static void draw_tile(const TileMap &map, const DrawableTile &dt, int scale)
{
    Rectangle destination = {dt.world_x * scale, dt.world_y * scale,
                              (float)map.tile_size * scale, (float)map.tile_size * scale};
    for (const auto &tileset : map.tilesets)
    {
        if (dt.tile_id >= tileset.first_gid &&
            dt.tile_id < tileset.first_gid + tileset.tile_count)
        {
            int local_id = dt.tile_id - tileset.first_gid;
            int col = local_id % tileset.columns;
            int row = local_id / tileset.columns;
            Rectangle src = {(float)(col * tileset.tile_size), (float)(row * tileset.tile_size),
                              (float)tileset.tile_size, (float)tileset.tile_size};
            DrawTexturePro(tileset.texture, src, destination, {0, 0}, 0, WHITE);
            return;
        }
    }
}

void tilemap_draw_object(const TileMap &map, int scale)
{
    for (const auto &dt : map.object_tiles)
        draw_tile(map, dt, scale);
}
