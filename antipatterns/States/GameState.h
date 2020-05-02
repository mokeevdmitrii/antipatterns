//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMESTATE_H
#define ANTIPATTERNS_GAMESTATE_H

#include "State.h"
#include "../src/EnemySystem.h"
#include "../Enemies/Rat.h"
#include "../src/TileMap.h"
#include "../src/Room.h"
#include "../Resources/Filenames.h"

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
    /* initializers */
    void InitKeybindings() override;
    void InitTextures();
    void InitPlayer();
    void InitPauseMenu();
    void InitRooms();
    void InitUniqueExits();
    void InitUniqueEnemies();
    void AddUniqueEnemy(EnemyType enemy_type, const std::shared_ptr<Enemy>& enemy);
    void InitUniqueTiles();


    void ChangeRoom(ROOM_ID old_room, ROOM_ID new_room);

    /* thinking about moving player somewhere else */
    static const std::unordered_map<std::string, ROOM_ID> names_to_room_ids_;
    std::unordered_map<ROOM_ID, std::unique_ptr<Room>> rooms_;
    Room* current_room_{nullptr};
    std::shared_ptr<Creature> player_;
    std::shared_ptr<std::unordered_map<EnemyType, std::shared_ptr<Enemy>>> unique_enemies_;
    std::shared_ptr<std::unordered_map<TileType, std::unique_ptr<Tile>>> unique_tiles_;
    std::shared_ptr<std::unordered_map<ExitType, std::unique_ptr<Exit>>> unique_exits_;
    std::shared_ptr<PauseMenu> pause_menu_;
};


#endif //ANTIPATTERNS_GAMESTATE_H
