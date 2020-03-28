//
// Created by dmitry on 3/27/20.
//

#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game {
private:
    /* variables */
    std::unique_ptr<sf::RenderWindow> _window;
    sf::Event _event;

    /* initializers */
    void InitWindow();
public:
    /* constructors / destructors */
    Game();
    virtual ~Game();

    /* functions */
    void Update();
    void Run();
    void UpdateEvents();
    /* думаю насчёт выделения Render() в отдельный класс */
    /* возможно это не нужно, т.к. в этой реализации
     * графической библиотеки окно рендерит всё само */
    void Render();

};

#endif //ANTIPATTERNS_GAME_H
