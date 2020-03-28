//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<std::unordered_map<std::string, int>> supported_keys) :
        State(std::move(window), std::move(supported_keys)) {
    GameState::InitKeybindings();
}

GameState::~GameState() {

}

/* overrided functions */

void GameState::EndState() {
    std::cout << "GameState ending" << std::endl;
}

void GameState::Update(const float time_elapsed) {
    UpdateInput(time_elapsed);
    _player.Update(time_elapsed);
}

void GameState::UpdateInput(const float time_elapsed) {
    CheckQuit();

    /* temporary handling player input - to be reworked */
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_LEFT")))) {
        _player.Move(time_elapsed, sf::Vector2f(-1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_DOWN")))) {
        _player.Move(time_elapsed, sf::Vector2f(0.f, 1.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_RIGHT")))) {
        _player.Move(time_elapsed, sf::Vector2f(1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_UP")))) {
        _player.Move(time_elapsed, sf::Vector2f(0.f, -1.f));
    }
}

void GameState::Render(std::shared_ptr<sf::RenderTarget> target) {
    if (target == nullptr) {
        target = _window;
    }
    _player.Render(target);
}

void GameState::InitKeybindings() {
    std::ifstream in("../Config/gamestate_keybindings.txt");
    if (in.is_open()) {
        std::string key_str;
        std::string key_bind;
        while (in >> key_str >> key_bind) {
            _keybindings.try_emplace(key_str, _supported_keys->at(key_bind));
        }
    }
}





