//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMESTATE_H
#define ANTIPATTERNS_GAMESTATE_H

#include "State.h"

class GameState : public State {
public:
    GameState(std::shared_ptr<sf::RenderWindow> window);
    virtual ~GameState();

    /* overrided functions */
    void Update(float time_elapsed) override;
    void Render(std::shared_ptr<sf::RenderTarget> target) override;
    void EndState() override;
    void UpdateKeyBinds(float time_elapsed) override;

private:
    GameObject player;
};


#endif //ANTIPATTERNS_GAMESTATE_H
