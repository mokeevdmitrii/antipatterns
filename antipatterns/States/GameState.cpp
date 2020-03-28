//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

GameState::GameState(std::shared_ptr<sf::RenderWindow> window) : State(std::move(window)) {

}

GameState::~GameState() {

}

/* overrided functions */

void GameState::EndState() {
    std::cout << "GameState ending" << std::endl;
}

void GameState::Update(float time_elapsed) {
    UpdateKeyBinds(time_elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        std::cout << "A pressed" << std::endl;
    }
}

void GameState::Render(std::shared_ptr<sf::RenderTarget> target) {

}

void GameState::UpdateKeyBinds(float time_elapsed) {
    CheckQuit();
}


