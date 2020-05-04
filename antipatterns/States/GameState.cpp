//
// Created by dmitry on 3/28/20.
//

#include "GameState.h"

#include <utility>

const std::unordered_map<std::string, ROOM_ID> GameState::rooms_names_to_ids = {
        {"init_room",   ROOM_ID::INIT_ROOM},
        {"second_room", ROOM_ID::SECOND_ROOM}
};


GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
                     std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack) :
        State(std::move(window), std::move(supported_keys), std::move(state_stack)) {
    GameState::InitKeybindings();
    GameState::InitPlayer();
    GameState::InitRooms();
    GameState::InitPauseMenu();
    GameState::InitInputHandler();
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
        std::unique_ptr<GameCommand> last_command = input_handler_->UpdateInput(time_elapsed);
        if (last_command != nullptr) {
            last_command->Execute(time_elapsed);
        }
        for (auto& [id, room_ptr] : rooms_) {
            room_ptr->Update(time_elapsed);
        }
        const Exit* active_exit = rooms_.at(current_room_id)->GetActiveExit();
        if (active_exit != nullptr) {
            std::cout << (int) current_room_id << " " << (int) active_exit->GetRoomIdTo() << std::endl;
            ChangeRoom(current_room_id, active_exit->GetRoomIdTo());
        }

        // вызывать проверку на переход в другую комнату !
        /* if (current_room_id->GetRoomID() != current_room_id->GetCurrentRoomID()) {
         * ChangeRoom(current_room_id->GetRoomID(), current_room_id->GetCurrentRoomID());
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
    rooms_.at(current_room_id)->Render(*target);
    if (_paused) {
        pause_menu_->Render(*target);
    }
}

void GameState::ChangeRoom(ROOM_ID old_room, ROOM_ID new_room) {
    rooms_.at(new_room)->SetPlayer(player_);
    current_room_id = new_room;
    player_->SetPosition(sf::Vector2f(100, 100));
    rooms_.at(old_room)->SetPlayer(nullptr);
}


/* initializers */

void GameState::InitKeybindings() {
    std::ifstream in(file::kGameStateKeybindingsFile);
    if (in.is_open()) {
        std::string key_str;
        std::string key_bind;
        while (in >> key_str >> key_bind) {
            keybindings_->try_emplace(key_str, supported_keys_->at(key_bind));
        }
    }
}

void GameState::InitPlayer() {
    player_ = std::make_shared<Player>(sf::Vector2f(0, 0), UniqueDatabase::Instance().GetData().textures.at("PLAYER"),
                                       "../Config/player_settings.json");
}

void GameState::InitPauseMenu() {
    pause_menu_ = std::make_shared<PauseMenu>(window_);
}

void GameState::InitRooms() {
    const std::map<std::string, Json::Node> rooms_settings = Json::Load("../Config/rooms.json").GetRoot().AsMap();
    for (const auto&[room_name, room_settings_json] : rooms_settings) {
        const auto &room_settings = room_settings_json.AsMap();
        ROOM_ID room_id = rooms_names_to_ids.at(room_name);
        rooms_[room_id] = std::make_unique<Room>(room_settings.at("file_name").AsString());
        std::string exits_file_name = room_settings.at("exits").AsString();
        const std::vector<Json::Node> room_exits_settings = Json::Load(exits_file_name).GetRoot().AsArray();
        for (const auto &exit_node : room_exits_settings) {
            const auto &exit_settings_map = exit_node.AsMap();
            ExitType curr_type = static_cast<ExitType>(exit_settings_map.at("type").AsDouble());
            std::unique_ptr<Exit> curr_exit = std::make_unique<Exit>(*UniqueDatabase::Instance().GetData().exits.at(curr_type));
            curr_exit->LoadFromMap(exit_settings_map.at("settings").AsMap());
            rooms_.at(room_id)->AddExit(std::move(curr_exit));
        }
        current_room_id = ROOM_ID::INIT_ROOM;
        rooms_.at(current_room_id)->SetPlayer(player_);
    }
}

void GameState::InitInputHandler() {
    input_handler_ = std::make_unique<PlayerInputHandler>(player_, keybindings_);
}














