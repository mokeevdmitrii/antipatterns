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
    sf::Event event_{};

    sf::Clock game_clock_;
    float time_elapsed_{};

    GraphicsSettings _graphics_settings;
    /*variables that are passed to State class*/
    std::shared_ptr<sf::RenderWindow> window_;
    std::shared_ptr<std::stack<std::shared_ptr<State>>> states_;
    std::shared_ptr<std::unordered_map<std::string, int>> supported_keys_;
};


#endif //ANTIPATTERNS_GAME_H
