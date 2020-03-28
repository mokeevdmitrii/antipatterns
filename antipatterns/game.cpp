//
// Created by dmitry on 3/27/20.
//

#include "game.h"


/* Constructors / Destructors */
Game::Game() {
    InitWindow();
}

Game::~Game() {

}

/* Static functions */


/* Initializers */
void Game::InitWindow() {
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Antipatterns");
}

/* Functions */
void Game::Update() {
    UpdateEvents();
}

void Game::Render() {
    _window->clear();

    /* draw everything here */

    _window->display();
}

void Game::Run() {
    while (_window->isOpen())
    {
        Update();
        Render();
    }
}

void Game::UpdateEvents() {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
    }
}




