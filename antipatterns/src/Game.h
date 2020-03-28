//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAME_H
#define ANTIPATTERNS_GAME_H

#include <iostream>
#include <ctime>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Game {
public:
    /* constructors, destructors */
    Game();
    virtual ~Game();
    /* functions */
    void Run();
    void Update();
    void UpdateEvents();
    void Render();
private:
    /* initializers */
    void InitWindow();
    /* variables */
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Event _event;
};


#endif //ANTIPATTERNS_GAME_H
