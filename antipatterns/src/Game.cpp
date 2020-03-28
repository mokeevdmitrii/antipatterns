//
// Created by dmitry on 3/28/20.
//

#include "Game.h"
#include "../States/GameState.h"

/* Constructors, destructors */

Game::Game() {
    InitWindow();
    InitKeys();
    InitStates();
}

Game::~Game() {
    /* no need to delete std::shared_ptr<sf::RenderWindow> here */
    while (!_states.empty()) {
        _states.pop();
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
    if (!_states.empty()) {
        _states.top()->Update(_time_elapsed);
        if (_states.top()->IsQuitting()) {
            /* animation, saving */
            _states.top()->EndState();
            _states.pop();
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
    if (!_states.empty()) {
        _states.top()->Render(_window);
    }

    _window->display();
}

void Game::EndApplication() {
    std::cout << "Application Ending" << std::endl;
}

/* initializers */

void Game::InitWindow() {
    /* Creates a window from using config settings file */

    std::ifstream in("../Config/window_init.txt");
    std::string game_title{};
    unsigned int max_frame_limit = 60;
    sf::VideoMode window_bounds(800, 600);
    bool vertical_sync_enabled{};

    if (in.is_open()) {
        std::getline(in, game_title);
        in >> window_bounds.width >> window_bounds.height;
        in >> max_frame_limit;
        in >> vertical_sync_enabled;
    }

    in.close();

    _window = std::make_shared<sf::RenderWindow>(window_bounds, game_title);
    _window->setFramerateLimit(max_frame_limit);
    _window->setVerticalSyncEnabled(vertical_sync_enabled);
}

/*init keys must be used before init states, or program crashes - to fix*/
void Game::InitKeys() {
    std::ifstream in("../Config/supported_keys.txt");
    if (in.is_open()) {
        std::string key_str;
        int key_val;
        while (in >> key_str >> key_val) {
            _supported_keys.try_emplace(key_str, static_cast<sf::Keyboard::Key>(key_val));
        }
    }
}

void Game::InitStates() {
    _states.push(std::make_shared<MainMenuState>(_window, std::make_shared<std::unordered_map<std::string, int>>(_supported_keys)));
}







