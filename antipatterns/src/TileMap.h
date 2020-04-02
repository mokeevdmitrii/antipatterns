//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_TILEMAP_H
#define ANTIPATTERNS_TILEMAP_H

#include "Tile.h"
#include "Creature.h"

class TileMap {
public:
    TileMap();
    ~TileMap();

    void UpdateTiles(std::unique_ptr<Creature>, float time_elapsed /*, EnemySystem &system */);
    void Render(sf::RenderTarget& target);

private:
    std::vector<std::vector<std::shared_ptr<Tile>>> _map;
    static std::unordered_map<TileType, std::shared_ptr<Tile>> _tiles;
};


#endif //ANTIPATTERNS_TILEMAP_H
