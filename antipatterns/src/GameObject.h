//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_GAMEOBJECT_H
#define ANTIPATTERNS_GAMEOBJECT_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <string>
#include "../Resources/GraphicsSettings.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class GameObject {
public:
    GameObject();

    virtual ~GameObject();

    /* functions */
    virtual void Update(float time_elapsed);
    virtual void Render(const std::shared_ptr<sf::RenderTarget> &target);
    /* do not change signature */
    virtual void Move(float time_elapsed, const sf::Vector2f &direction);

    void InitSprite(std::shared_ptr<sf::Texture> texture);

protected:
    float _move_speed;

    /* for drawing */
    std::shared_ptr<sf::Texture> _texture;
    sf::Sprite _sprite;
private:

};


#endif //ANTIPATTERNS_GAMEOBJECT_H
