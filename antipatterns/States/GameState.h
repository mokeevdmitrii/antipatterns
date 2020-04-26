//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMESTATE_H
#define ANTIPATTERNS_GAMESTATE_H

#include "State.h"
#include "../src/EnemySystem.h"
#include "../Enemies/Rat.h"
#include "../src/TileMap.h"

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
    void InitEnemySystem();
    void InitTileMap();
    void InitPauseMenu();

    /* thinking about moving player somewhere else */
    std::unique_ptr<Creature> _player;
    std::unique_ptr<EnemySystem> _enemy_system;
    std::unique_ptr<TileMap> _tile_map;
    std::shared_ptr<PauseMenu> _pause_menu;
};


#endif //ANTIPATTERNS_GAMESTATE_H
