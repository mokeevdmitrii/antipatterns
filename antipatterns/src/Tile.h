//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_TILE_H
#define ANTIPATTERNS_TILE_H

#include "../Resources/GraphicsSettings.h"

enum TileType {
    BRICK = 0,
    SAND = 1,
    GRASS = 2,
    MUD = 3,
    YELLOW_BRICK = 4
};

class Tile {
public:
    Tile(TileType type, const sf::Texture &texture,
            const sf::IntRect &rect, const sf::Vector2f &pos = sf::Vector2f());

    std::unique_ptr<Tile> Clone(const sf::Vector2f& position) const;

    void Render(sf::RenderTarget& target) const;
private:
    sf::Sprite _sprite;
    TileType _type;
};


#endif //ANTIPATTERNS_TILE_H
