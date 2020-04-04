//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
                     std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack) :
         _pause_menu(window), State(window, std::move(supported_keys), std::move(state_stack)) {
    GameState::InitKeybindings();
    GameState::InitTextures();
    GameState::InitPlayer();
    GameState::InitEnemySystem();
    GameState::InitTileMap();
}

GameState::~GameState() {

}

/* overrided functions */


void GameState::Update(const float time_elapsed) {
    /* if not paused, update game */
    UpdateMousePositions();
    if (!_paused) {
        UpdateInput(time_elapsed);
        UpdatePlayerInput(time_elapsed);
        _player->Update(time_elapsed);
        _enemy_system->Update(time_elapsed);
    /* else update pause menu */
    } else {
        _pause_menu.Update(_mouse_positions.view);
        if (_pause_menu.IsButtonActive(std::string("UNPAUSE_GAME"))) {
            Unpause();
        }
    }
}

void GameState::UpdateInput(const float time_elapsed) {
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("PAUSE")))) {
        Pause();
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("CLOSE")))) {
        End();
    }
}

void GameState::Render(std::shared_ptr<sf::RenderTarget> target) {
    _tile_map->Render(*target);
    _enemy_system->Render(*target);
    _player->Render(*target);
    if (_paused) {
        _pause_menu.Render(*target);
    }
}

void GameState::UpdatePlayerInput(float time_elapsed) {
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_LEFT")))) {
        _player->Move(time_elapsed, sf::Vector2f(-1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_DOWN")))) {
        _player->Move(time_elapsed, sf::Vector2f(0.f, 1.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_RIGHT")))) {
        _player->Move(time_elapsed, sf::Vector2f(1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(_keybindings.at("MOVE_UP")))) {
        _player->Move(time_elapsed, sf::Vector2f(0.f, -1.f));
    }
}

/* initializers */

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

void GameState::InitTextures() {
    if (!_textures["PLAYER"].loadFromFile("../Images/Sprites/Player/hero.png")) {
        throw std::runtime_error("Player texture cannot be loaded from file");
    }
}

void GameState::InitPlayer() {
    _player = std::make_unique<Player>(sf::Vector2f(0,0), _textures.at("PLAYER"), "../Config/player_settings.json");
}

void GameState::InitEnemySystem() {
    _enemy_system = std::make_unique<EnemySystem>();
    std::map<std::string, Json::Node> enemy_settings = Json::Load("../Config/enemies_settings.json").GetRoot().AsMap();
    _enemy_system->AddEnemy(std::make_unique<Rat>(sf::Vector2f(0,0), _textures.at("PLAYER"), enemy_settings.at("Rat").AsMap()));
    _enemy_system->CreateEnemy(0, sf::Vector2f(80, 100), 1);
}

void GameState::InitTileMap() {
    _tile_map = std::make_unique<TileMap>("../Config/unique_tiles.json", "../Config/init_map.json");
}









