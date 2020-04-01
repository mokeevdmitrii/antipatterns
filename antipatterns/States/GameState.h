//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMESTATE_H
#define ANTIPATTERNS_GAMESTATE_H

#include "State.h"

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
    /* class functions */
    void UpdatePlayerInput(float time_elapsed);
private:
    /* initializers */
    void InitKeybindings() override;
    void InitTextures();
    void InitPlayer();
    std::unique_ptr<Creature> _player;
    PauseMenu _pause_menu;
};


#endif //ANTIPATTERNS_GAMESTATE_H
