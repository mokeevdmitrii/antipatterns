//
// Created by dmitry on 3/28/20.
//

#include "State.h"

#include <utility>

/* Constructors and destructors */
State::State(std::shared_ptr<sf::RenderWindow> window,
             std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
             std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack)
        : _window(std::move(window)),
        _supported_keys(std::move(supported_keys)),
        _state_stack(std::move(state_stack)) {
    State::InitKeybindings();
}

State::~State() {

}

bool State::GetToQuit() const {
    return _to_quit;
}

void State::UpdateMousePositions() {
    _mouse_positions.screen = sf::Mouse::getPosition();
    _mouse_positions.window = sf::Mouse::getPosition(*_window);
    _mouse_positions.view = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
}

void State::End() {
    _to_quit = true;
}

void State::Pause() {
    _paused = true;
}

void State::Unpause() {
    _paused = false;
}

void State::InitKeybindings() {
    _keybindings = std::make_shared<std::unordered_map<std::string, int>>();
}




