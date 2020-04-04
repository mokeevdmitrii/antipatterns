//
// Created by dmitry on 4/1/20.
//

#ifndef ANTIPATTERNS_HITBOXCOMPONENT_H
#define ANTIPATTERNS_HITBOXCOMPONENT_H


#include <SFML/Graphics.hpp>
#include "../Resources/Json.h"

class HitboxComponent {
public:
    HitboxComponent(sf::Sprite& sprite, const std::map<std::string, Json::Node> &settings);
    ~HitboxComponent();

    /* initializer */
    void LoadFromMap(const std::map<std::string, Json::Node>& settings);

    void Update();
    void Render(sf::RenderTarget& target);

    void SetPosition(const sf::Vector2f& position);
    void UpdateCopy(sf::Sprite& sprite);

    bool CheckCollision(const sf::FloatRect& other);
private:
    sf::RectangleShape _hitbox;
    sf::Sprite* _sprite;
    sf::Vector2f _offset;
};


#endif //ANTIPATTERNS_HITBOXCOMPONENT_H
