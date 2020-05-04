//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMESTATE_H
#define ANTIPATTERNS_GAMESTATE_H

#include "State.h"
#include "../src/Input/InputHandler.h"
#include "../src/EnemySystem.h"
#include "../src/TileMap.h"
#include "../src/Room.h"
#include "../Resources/Constants/Filenames.h"

class GameState : public State {
public:
    GameState(std::shared_ptr<sf::RenderWindow> window,
            std::shared_ptr<std::unordered_map<std::string, int>> supported_keys,
            std::shared_ptr<std::stack<std::shared_ptr<State>>> state_stack);
    virtual ~GameState();

    /* overrided functions */
    void Update(float time_elapsed) override;
    void UpdateInput(float time_elapsed) override;
    void Render(std::shared_ptr<sf::RenderTarget> target) override;
private:
    void ChangeRoom(ROOM_ID old_room, ROOM_ID new_room);

    /* initializers */
    void InitKeybindings() override;
    void InitPlayer();
    void InitPauseMenu();
    void InitRooms();
    void InitInputHandler();

    /* thinking about moving player somewhere else */
    static const std::unordered_map<std::string, ROOM_ID> rooms_names_to_ids;
    std::unordered_map<ROOM_ID, std::unique_ptr<Room>> rooms_;
    ROOM_ID current_room_id{ROOM_ID::INIT_ROOM};
    std::shared_ptr<Creature> player_;
    std::shared_ptr<PauseMenu> pause_menu_;
    std::unique_ptr<PlayerInputHandler> input_handler_;
};


#endif //ANTIPATTERNS_GAMESTATE_H
