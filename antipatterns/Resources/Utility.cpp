//
// Created by dmitry on 5/1/20.
//

#include "Utility.h"

namespace Utility {

    float GetDistance(sf::Vector2f lhs, sf::Vector2f rhs) {
        float delta_x = rhs.x - lhs.x, delta_y = rhs.y - lhs.y;
        return sqrtf(delta_x * delta_x + delta_y * delta_y);
    }

}