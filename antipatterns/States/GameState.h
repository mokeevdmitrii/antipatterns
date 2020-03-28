//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMESTATE_H
#define ANTIPATTERNS_GAMESTATE_H

#include "State.h"

class GameState : public State {
public:
    GameState(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<std::unordered_map<std::string, int>> supported_keys);
    virtual ~GameState();

    /* overrided functions */
    void Update(float time_elapsed) override;
    void UpdateInput(float time_elapsed) override;
    void Render(std::shared_ptr<sf::RenderTarget> target) override;
    void EndState() override;
private:
    void InitKeybindings() override;
    GameObject _player;
};


#endif //ANTIPATTERNS_GAMESTATE_H
