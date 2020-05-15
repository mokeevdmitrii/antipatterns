//
// Created by dmitry on 5/1/20.
//

#include "Utility.h"

namespace utility {

float GetDistance(sf::Vector2f lhs, sf::Vector2f rhs) {
  float delta_x = rhs.x - lhs.x, delta_y = rhs.y - lhs.y;
  return sqrtf(delta_x * delta_x + delta_y * delta_y);
}
sf::FloatRect CreateSideRect(sf::Vector2f start, sf::Vector2f end) {
  float width = phys_const::kHitboxRecSide * (end.x - start.x);
  float height = phys_const::kHitboxRecSide * (end.y - start.y);
  float x = start.x + (1.0f - phys_const::kHitboxRecSide) / 2 * (end.x - start.x);
  float y = start.y + (1.0f - phys_const::kHitboxRecSide) / 2 * (end.y - start.y);
  return {{x, y}, {width, height}};

}

} // namespace utility