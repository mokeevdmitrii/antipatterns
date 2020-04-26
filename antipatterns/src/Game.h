//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAME_H
#define ANTIPATTERNS_GAME_H


#include "../States/MainMenuState.h"


class Game {
public:
    /* constructors, destructors */
    Game();
    ~Game();
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
    sf::Event _event{};

    sf::Clock clock;
    float _time_elapsed{};

    GraphicsSettings _graphics_settings;
    /*variables that are passed to State class*/
    std::shared_ptr<sf::RenderWindow> _window;
    std::shared_ptr<std::stack<std::shared_ptr<State>>> _states;
    std::shared_ptr<std::unordered_map<std::string, int>> _supported_keys;
};


#endif //ANTIPATTERNS_GAME_H
