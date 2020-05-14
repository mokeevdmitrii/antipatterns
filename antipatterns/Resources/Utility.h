//
// Created by dmitry on 5/1/20.
//

#ifndef ANTIPATTERNS_UTILITY_H
#define ANTIPATTERNS_UTILITY_H

#include "../src/Tile.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <type_traits>

namespace Utility {

float GetDistance(sf::Vector2f lhs, sf::Vector2f rhs);

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

} // namespace Utility

#endif // ANTIPATTERNS_UTILITY_H
