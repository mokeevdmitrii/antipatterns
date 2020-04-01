//
// Created by dmitry on 3/28/20.
//

#include "Game.h"
#include "../States/GameState.h"

/* Constructors, destructors */

Game::Game() {
    InitWindow();
    /* init keys before init states */
    InitKeys();
    /* do not put before init keys */
    InitStates();
}

Game::~Game() {
    while (!_states->empty()) {
        _states->pop();
    }
}

/* Functions */

void Game::Run() {
    while (_window->isOpen()) {
        UpdateTime();
        Update();
        Render();
    }
}

void Game::Update() {
    UpdateEvents();
    if (!_states->empty()) {
        _states->top()->Update(_time_elapsed);
        if (_states->top()->GetToQuit()) {
            /* animation, saving */
            //_states->top()->End();
            _states->pop();
        }
    } else {
        /* no states left, we are closing the game */
        EndApplication();
        _window->close();
    }
}

void Game::UpdateEvents() {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window->close();
        }
    }
}

void Game::UpdateTime() {
    /* get how much time elapsed while drawing one frame */
    _time_elapsed = clock.restart().asSeconds();
}

void Game::Render() {
    _window->clear();

    /* draw everything here actually */
    if (!_states->empty()) {
        _states->top()->Render(_window);
    }

    _window->display();
}

void Game::EndApplication() {
    std::cout << "Application Ending" << std::endl;
}

/* initializers */

void Game::InitWindow() {
    /* Creates a window from using config settings file */
    if (!_graphics_settings.LoadFromFile("../Config/window_init.txt")) {
        throw std::runtime_error("settings not found");
    }

    if (_graphics_settings._fullscreen) {
        _window = std::make_shared<sf::RenderWindow>(_graphics_settings._resolution,
                                                     _graphics_settings._game_title, sf::Style::Fullscreen,
                                                     _graphics_settings._settings);
    } else {
        _window = std::make_shared<sf::RenderWindow>(_graphics_settings._resolution,
                                                     _graphics_settings._game_title,
                                                     sf::Style::Titlebar | sf::Style::Close,
                                                     _graphics_settings._settings);
    }
    _window->setFramerateLimit(_graphics_settings._framerate_limit);
    _window->setVerticalSyncEnabled(_graphics_settings._v_sync_enabled);
}

/*init keys must be used before init states, or program crashes - to fix*/
void Game::InitKeys() {
    _supported_keys = std::make_shared<std::unordered_map<std::string, int>>();
    std::ifstream in("../Config/supported_keys.txt");
    if (in.is_open()) {
        std::string key_str{};
        int key_val{};
        while (in >> key_str >> key_val) {
            _supported_keys->try_emplace(key_str, static_cast<sf::Keyboard::Key>(key_val));
        }
    }
}

void Game::InitStates() {
    _states = std::make_shared<std::stack<std::shared_ptr<State>>>();
    _states->push(std::make_shared<MainMenuState>(_window, _supported_keys, _states));
}







