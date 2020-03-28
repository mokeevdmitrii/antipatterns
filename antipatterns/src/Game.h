//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAME_H
#define ANTIPATTERNS_GAME_H

#include <iostream>
#include <ctime>
#include "Clock.h"
#include "../States/GameState.h"


class Game {
public:
    /* constructors, destructors */
    Game();
    virtual ~Game();
    /* functions */
    /* updating */
    void Update();
    void UpdateEvents();
    void UpdateTime();

    /* running */
    void Run();

    /* rendering */
    void Render();

    /* ending */
    void EndApplication();
private:
    /* initializers */
    void InitWindow();
    void InitKeys();
    void InitStates();
    /* variables */
    std::shared_ptr<sf::RenderWindow> _window;
    sf::Event _event{};

    Clock clock;
    float _time_elapsed{};

    std::stack<std::shared_ptr<State>> _states;

    std::unordered_map<std::string, int> _supported_keys;
};


#endif //ANTIPATTERNS_GAME_H
