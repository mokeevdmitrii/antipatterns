//
// Created by dmitry on 4/29/20.
//

#ifndef ANTIPATTERNS_CONSTANTS_H
#define ANTIPATTERNS_CONSTANTS_H

#include <SFML/Window/Keyboard.hpp>
#include <limits>

const double kDInfinity = std::numeric_limits<double>::infinity();
const float kFInfinity = std::numeric_limits<float>::infinity();

const float kNormalHeight = 600;
const float kNormalWidth = 800;

const sf::Keyboard::Key kUnknownKey = sf::Keyboard::BackSlash;

#endif // ANTIPATTERNS_CONSTANTS_H
