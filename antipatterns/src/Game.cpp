//
// Created by dmitry on 3/28/20.
//

#include "Game.h"

/* Constructors, destructors */

Game::Game() {
    InitWindow();
}

Game::~Game() {
    /* no need to delete std::unique_ptr<sf::RenderWindow> here */
}

/* Functions */

void Game::Run() {
    while (_window->isOpen()) {
        Update();
        Render();
    }
}

void Game::Update() {
    UpdateEvents();
}

void Game::UpdateEvents() {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
    }
}

void Game::Render() {
    _window->clear();

    /* draw everything here actually */

    _window->display();
}

void Game::InitWindow() {
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "antipatterns roguelike");
}




