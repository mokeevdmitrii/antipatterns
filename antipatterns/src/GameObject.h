//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMEOBJECT_H
#define ANTIPATTERNS_GAMEOBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class GameObject {
public:
    GameObject();

    virtual ~GameObject();

    virtual void Update(float time_elapsed);
    virtual void Render(const std::shared_ptr<sf::RenderTarget>& target);
    virtual void Move(float time_elapsed, const sf::Vector2f &direction);

protected:
    sf::RectangleShape _shape;
    float _move_speed;
private:

};


#endif //ANTIPATTERNS_GAMEOBJECT_H
