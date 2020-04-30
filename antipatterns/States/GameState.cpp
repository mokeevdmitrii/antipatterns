//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

const std::unordered_map<std::string, ROOM_ID> GameState::names_to_room_ids_ = {
        {"init_room", ROOM_ID::INIT_ROOM}, {"boss_room", ROOM_ID::BOSS_ROOM}
};


GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
                     std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack) :
        State(std::move(window), std::move(supported_keys), std::move(state_stack)) {
    GameState::InitKeybindings();
    GameState::InitTextures();
    GameState::InitPlayer();
    GameState::InitUniqueTiles();
    GameState::InitUniqueEnemies();
    GameState::InitRooms();
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
        current_room_->Update(time_elapsed);
        //player_->Update(time_elapsed);
        //enemy_system_->Update(time_elapsed);

        // вызывать проверку на переход в другую комнату !
        /* if (current_room_->GetRoomID() != current_room_->GetCurrentRoomID()) {
         * ChangeRoom(current_room_->GetRoomID(), current_room_->GetCurrentRoomID());
         * }
        * else update pause menu */
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
    current_room_->Render(*target);
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
    player_ = std::make_shared<Player>(sf::Vector2f(0, 0), textures_.at("PLAYER"), "../Config/player_settings.json",
                                       keybindings_);
}

void GameState::InitPauseMenu() {
    pause_menu_ = std::make_shared<PauseMenu>(window_);
}

void GameState::InitRooms() {
    const std::map<std::string, Json::Node> rooms_settings = Json::Load("../Config/rooms.json").GetRoot().AsMap();
    for (const auto& [room_name, room_file_node] : rooms_settings) {
        rooms_[names_to_room_ids_.at(room_name)] = std::make_unique<Room>(room_file_node.AsString());
    }
    current_room_ = rooms_.at(ROOM_ID::INIT_ROOM).get();
    current_room_->SetPlayer(player_);
}

void GameState::InitUniqueEnemies() {
    unique_enemies_ = std::make_shared<std::unordered_map<EnemyType, std::shared_ptr<Enemy>>>();
    const std::map<std::string, Json::Node> enemy_settings = Json::Load(
            "../Config/enemies_settings.json").GetRoot().AsMap();
    /* index 0 */
    AddUniqueEnemy(EnemyType::ENEMY_SPAWNER, std::make_shared<EnemySpawner>(textures_.at("PLAYER"), enemy_settings.at("EnemySpawner").AsMap()));
    /* index 1 will fix this ****-code later*/
    AddUniqueEnemy(EnemyType::RAT, std::make_shared<Rat>(textures_.at("PLAYER"), enemy_settings.at("Rat").AsMap()));
    EnemySystem::SetUniqueEnemies(unique_enemies_);
}

void GameState::AddUniqueEnemy(EnemyType enemy_type, const std::shared_ptr<Enemy>& enemy) {
    if(!unique_enemies_->try_emplace(enemy_type, enemy).second) {
        throw std::runtime_error("You didn't load all enemies");
    }
}

void GameState::InitUniqueTiles() {
    unique_tiles_ = std::make_shared<std::unordered_map<TileType, std::unique_ptr<Tile>>>();
    std::map<std::string, Json::Node> settings = Json::Load("../Config/unique_tiles.json").GetRoot().AsMap();
    std::string texture_file = settings.at("file_name").AsString();
    textures_["TILE_MAP"].loadFromFile(texture_file);
    int grid_size = static_cast<int>(settings.at("grid_size").AsDouble());
    TileMap::SetGridSize(grid_size);
    for (const auto& settings_map : settings.at("tiles").AsArray()) {
        sf::IntRect curr_rect;
        TileType curr_type;
        curr_rect.height = curr_rect.width = TileMap::GetGridSize();
        curr_rect.left = static_cast<int>(settings_map.AsMap().at("x").AsDouble()) * grid_size;
        curr_rect.top = static_cast<int>(settings_map.AsMap().at("y").AsDouble()) * grid_size;
        curr_type = static_cast<TileType>(settings_map.AsMap().at("type").AsDouble());
        unique_tiles_->try_emplace(curr_type, std::make_unique<Tile>(curr_type, textures_.at("TILE_MAP"), curr_rect));
    }
    TileMap::SetUniqueTiles(unique_tiles_);
}











