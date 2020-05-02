//
// Created by dmitry on 5/1/20.
//

#ifndef ANTIPATTERNS_UTILITY_H
#define ANTIPATTERNS_UTILITY_H

#include <type_traits>
#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>
#include "../src/Tile.h"


class Segment {
private:
    constexpr static const float abs_eps = 10e-6;

public:
    Segment(sf::Vector2f first, sf::Vector2f second);

    bool Intersects(const Segment &other);

    bool ContainsPoint(sf::Vector2f point);
private:
    std::pair<sf::Vector2f, sf::Vector2f> points_;
};





#endif //ANTIPATTERNS_UTILITY_H
