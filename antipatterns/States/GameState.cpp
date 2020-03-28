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

void GameState::Update(const float time_elapsed) {
    UpdateKeyBinds(time_elapsed);
    player.Update(time_elapsed);
}

void GameState::Render(std::shared_ptr<sf::RenderTarget> target) {
    player.Render(target);
}

void GameState::UpdateKeyBinds(const float time_elapsed) {
    CheckQuit();
}


