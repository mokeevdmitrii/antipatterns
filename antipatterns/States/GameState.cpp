//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
                     std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack) :
        State(std::move(window), std::move(supported_keys), std::move(state_stack)) {
    GameState::InitKeybindings();
    GameState::InitTextures();
    GameState::InitPlayer();
    GameState::InitEnemySystem();
    GameState::InitTileMap();
    GameState::InitPauseMenu();
}

GameState::~GameState() {
    std::cout << "game destructed" << std::endl;
}

/* overrided functions */


void GameState::Update(const float time_elapsed) {
    /* if not paused, update game */
    UpdateMousePositions();
    if (!_paused) {
        UpdateInput(time_elapsed);
        player_->Update(time_elapsed);
        enemy_system_->Update(time_elapsed);
        /* else update pause menu */
    } else {
        pause_menu_->Update(mouse_positions_.view);
        if (pause_menu_->IsButtonActive(std::string("PLAY"))) {
            Unpause();
        }
        if (pause_menu_->IsButtonActive(std::string("QUIT"))) {
            End();
        }
    }
}

void GameState::UpdateInput(const float time_elapsed) {
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("PAUSE")))) {
        Pause();
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("CLOSE")))) {
        End();
    }
}

void GameState::Render(std::shared_ptr<sf::RenderTarget> target) {
    tile_map_->Render(*target);
    enemy_system_->Render(*target);
    player_->Render(*target);
    if (_paused) {
        pause_menu_->Render(*target);
    }
}

/* initializers */

void GameState::InitKeybindings() {
    std::ifstream in("../Config/gamestate_keybindings.txt");
    if (in.is_open()) {
        std::string key_str;
        std::string key_bind;
        while (in >> key_str >> key_bind) {
            keybindings_->try_emplace(key_str, supported_keys_->at(key_bind));
        }
    }
}

void GameState::InitTextures() {
    if (!textures_["PLAYER"].loadFromFile("../Images/Sprites/Player/hero.png")) {
        throw std::runtime_error("Player texture cannot be loaded from file");
    }
}

void GameState::InitPlayer() {
    player_ = std::make_unique<Player>(sf::Vector2f(0, 0), textures_.at("PLAYER"), "../Config/player_settings.json",
                                       keybindings_);
}

void GameState::InitEnemySystem() {
    enemy_system_ = std::make_unique<EnemySystem>(textures_, "../Config/enemies_settings.json",
                                                  "../Config/enemies_location.json");
    std::map<std::string, Json::Node> enemy_settings = Json::Load("../Config/enemies_settings.json").GetRoot().AsMap();
}

void GameState::InitTileMap() {
    tile_map_ = std::make_unique<TileMap>("../Config/unique_tiles.json", "../Config/init_map.json");
}

void GameState::InitPauseMenu() {
    pause_menu_ = std::make_shared<PauseMenu>(window_);
}










