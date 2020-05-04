//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_TILEMAP_H
#define ANTIPATTERNS_TILEMAP_H

#include "Tile.h"
#include "Creature.h"
#include "../Resources/Utility.h"


class TileMap {
    using Map = std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>>;
public:
    explicit TileMap(const std::string &map_tile_name, const std::unordered_map<TileType, std::unique_ptr<Tile>>& unique_tiles);

    ~TileMap() = default;

    template<typename T>

    void UpdateCreature(T &creature, float time_elapsed);

    void Render(sf::RenderTarget &target) const;

    static int GetGridSize();

    static void SetGridSize(int grid_size);

    sf::Vector2i GetGridPosition(sf::Vector2f global_position) const;

    sf::Vector2f GetGlobalPosition(sf::Vector2i grid_position) const;

    void AddTileLayer(TileType type, int x_pos, int y_pos, sf::Vector2f shift, const std::unordered_map<TileType, std::unique_ptr<Tile>>& unique_tiles);

private:
    /* initializers */
    void InitMap(const std::string &file_name, const std::unordered_map<TileType, std::unique_ptr<Tile>>& unique_tiles);

    std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>> map_;
    static int grid_size_;
    sf::Vector2i world_size_;
    sf::RectangleShape borders_;
};

template<typename T>
void TileMap::UpdateCreature(T &creature, float time_elapsed) {
    sf::RectangleShape hitbox = creature->GetHitbox();
    sf::Vector2f left_up_pos = hitbox.getPosition();
    sf::Vector2f size = hitbox.getSize();
    sf::Vector2f borders_pos = borders_.getPosition();
    sf::Vector2f borders_size = borders_.getSize();
    PossibleDirections new_directions = {left_up_pos.x >= borders_pos.x,
                                         (left_up_pos.x + size.x) <= borders_pos.x + borders_size.x,
                                         left_up_pos.y >= borders_pos.y,
                                         left_up_pos.y + size.y <= borders_pos.y + borders_size.y};
    creature->SetPossibleMoveDirections(new_directions);
}


#endif //ANTIPATTERNS_TILEMAP_H
