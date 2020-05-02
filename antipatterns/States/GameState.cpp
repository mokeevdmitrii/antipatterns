//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

const std::unordered_map<std::string, ROOM_ID> GameState::names_to_room_ids_ = {
        {"init_room",   ROOM_ID::INIT_ROOM},
        {"second_room", ROOM_ID::SECOND_ROOM}
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
    GameState::InitUniqueExits();
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
        if (current_room_->GetRoomID() != current_room_->GetCurrentRoomID()) {
            ChangeRoom(current_room_->GetRoomID(), current_room_->GetCurrentRoomID());
        }

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
    std::ifstream in(gamestate_keybindings_file);
    if (in.is_open()) {
        std::string key_str;
        std::string key_bind;
        while (in >> key_str >> key_bind) {
            keybindings_->try_emplace(key_str, supported_keys_->at(key_bind));
        }
    }
}

void GameState::InitTextures() {
    if (!textures_["PLAYER"].loadFromFile(player_texture_sheet_file)) {
        throw std::runtime_error("Player texture cannot be loaded from file");
    }
    if (!textures_["EXITS"].loadFromFile(exits_texture_sheet_file)) {
        throw std::runtime_error("Exits texture cannot be loaded from file");
    }
    if (!textures_["TILE_MAP"].loadFromFile(tileset_texture_sheet_file )) {
        throw std::runtime_error("Tiles textures cannot be loaded from file");
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
    for (const auto&[room_name, room_settings_json] : rooms_settings) {
        const auto &room_settings = room_settings_json.AsMap();
        ROOM_ID room_id = names_to_room_ids_.at(room_name);
        rooms_[room_id] = std::make_unique<Room>(room_settings.at("file_name").AsString());
        std::string exits_file_name = room_settings.at("exits").AsString();
        const std::vector<Json::Node> room_exits_settings = Json::Load(exits_file_name).GetRoot().AsArray();
        for (const auto &exit_node : room_exits_settings) {
            const auto &exit_settings_map = exit_node.AsMap();
            ExitType curr_type = static_cast<ExitType>(exit_settings_map.at("type").AsDouble());
            std::unique_ptr<Exit> curr_exit = std::make_unique<Exit>(*unique_exits_->at(curr_type));
            curr_exit->LoadFromMap(exit_settings_map.at("settings").AsMap());
            rooms_.at(room_id)->AddExit(std::move(curr_exit));
        }
        current_room_ = rooms_.at(ROOM_ID::INIT_ROOM).get();
        current_room_->SetPlayer(player_);
    }
}



void GameState::InitUniqueEnemies() {
    unique_enemies_ = std::make_shared<std::unordered_map<EnemyType, std::shared_ptr<Enemy>>>();
    const std::map<std::string, Json::Node> enemy_settings = Json::Load(
            unique_enemies_settings_file).GetRoot().AsMap();
    /* index 0 */
    AddUniqueEnemy(EnemyType::ENEMY_SPAWNER,
                   std::make_shared<EnemySpawner>(textures_.at("PLAYER"), enemy_settings.at("EnemySpawner").AsMap()));
    /* index 1 will fix this ****-code later*/
    AddUniqueEnemy(EnemyType::RAT,
                   std::make_shared<Rat>(textures_.at("PLAYER"), enemy_settings.at("Rat").AsMap()));
    EnemySystem::SetUniqueEnemies(unique_enemies_);
}

void GameState::AddUniqueEnemy(EnemyType enemy_type, const std::shared_ptr<Enemy> &enemy) {
    if (!unique_enemies_->try_emplace(enemy_type, enemy).second) {
        throw std::runtime_error("You didn't load all enemies");
    }
}

void GameState::InitUniqueTiles() {
    unique_tiles_ = std::make_shared<std::unordered_map<TileType, std::unique_ptr<Tile>>>();
    std::map<std::string, Json::Node> settings = Json::Load(unique_tiles_settings_file ).GetRoot().AsMap();
    int grid_size = static_cast<int>(settings.at("grid_size").AsDouble());
    TileMap::SetGridSize(grid_size);
    for (const auto &settings_map : settings.at("tiles").AsArray()) {
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

void GameState::InitUniqueExits() {
    unique_exits_ = std::make_shared<std::unordered_map<ExitType, std::unique_ptr<Exit>>>();
    const std::map<std::string, Json::Node> settings = Json::Load(unique_exits_settings_file).GetRoot().AsMap();
    const std::vector<Json::Node> &exits_nodes = settings.at("exits").AsArray();
    for (const auto &exit_node : exits_nodes) {
        const auto &exit_settings = exit_node.AsMap();
        sf::IntRect curr_rect{};
        ExitType exit_type;
        curr_rect.height = static_cast<int>(exit_settings.at("height").AsDouble());
        curr_rect.width = static_cast<int>(exit_settings.at("width").AsDouble());
        curr_rect.left = static_cast<int>(exit_settings.at("x").AsDouble());
        curr_rect.top = static_cast<int>(exit_settings.at("y").AsDouble());
        float exit_hitbox_width = exit_settings.at("hitbox_x").AsFloat();
        float exit_hitbox_height = exit_settings.at("hitbox_y").AsFloat();

        exit_type = static_cast<ExitType>(exit_settings.at("type").AsDouble());
        unique_exits_->try_emplace(exit_type, std::make_unique<Exit>(sf::RectangleShape(sf::Vector2f(exit_hitbox_width,
                                                                                                     exit_hitbox_height)), textures_.at("EXITS"), curr_rect));
    }
    Exit::SetUniqueExits(unique_exits_);
}

void GameState::ChangeRoom(ROOM_ID old_room, ROOM_ID new_room) {
    rooms_.at(new_room)->SetPlayer(player_);
    current_room_ = rooms_.at(new_room).get();
    player_->SetPosition(sf::Vector2f(100, 100));
    rooms_.at(old_room)->SetPlayer(nullptr);
}











