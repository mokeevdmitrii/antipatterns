//
// Created by dmitry on 4/2/20.
//

#include "Tile.h"

Tile::Tile(TileType type, const sf::Texture &texture, const sf::IntRect &rect,
           const sf::Vector2f &pos) : _type(type), _sprite(texture, rect) {
    _sprite.setPosition(pos);
}

std::unique_ptr<Tile> Tile::Clone(const sf::Vector2f &position) {
    auto new_tile = *this;
    new_tile._sprite.setPosition(position);
    return std::make_unique<Tile>(std::move(new_tile));
}

void Tile::Render(sf::RenderTarget &target) {
    target.draw(_sprite);
}


