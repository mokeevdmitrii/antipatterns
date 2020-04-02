//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_TILEMAP_H
#define ANTIPATTERNS_TILEMAP_H

#include "Tile.h"
#include "Creature.h"

class TileMap {
    using Map = std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>>;
public:
    TileMap(const std::string& settings_file_name, const std::string& map_tile_name);
    ~TileMap() = default;


    /* updating all the map */
    void UpdateTiles(std::unique_ptr<Creature> creature, float time_elapsed);
    void Render(sf::RenderTarget& target);

    sf::Vector2i GetGridPosition(sf::Vector2f global_position);
    sf::Vector2f GetGlobalPosition(sf::Vector2i grid_position);

private:
    /* initializers */
    /* initialize unique tiles parameters from a tile */
    void InitUniqueTiles(const std::string& file_name);
    void InitMap(const std::string& file_name);
    std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>> _map;
    std::unordered_map<TileType, std::unique_ptr<Tile>> _unique_tiles;
    int _grid_size;
    sf::Vector2i _world_size;
    sf::Texture _tile_sheet;
};


#endif //ANTIPATTERNS_TILEMAP_H
