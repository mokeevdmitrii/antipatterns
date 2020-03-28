//
// Created by dmitry on 3/28/20.
//

#include "State.h"

#include <utility>

/* Constructors and destructors */
State::State(std::shared_ptr<sf::RenderWindow> window) : _window(std::move(window)) {

}

State::~State() {

}

void State::CheckQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _to_quit = true;
    }
}

bool State::IsQuitting() const {
    return _to_quit;
}

