//
// Created by dmitry on 3/28/20.
//

#include "State.h"

#include <utility>

/* Constructors and destructors */
State::State(std::shared_ptr<sf::RenderWindow> window,
             std::shared_ptr<std::unordered_map<std::string, int>> supported_keys)
        : _window(std::move(window)), _supported_keys(std::move(supported_keys)) {

}

State::~State() {

}

void State::CheckQuit() {
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("CLOSE")))) {
        _to_quit = true;
    }
}

bool State::IsQuitting() const {
    return _to_quit;
}

