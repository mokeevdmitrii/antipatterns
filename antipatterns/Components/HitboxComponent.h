//
// Created by dmitry on 4/1/20.
//

#ifndef ANTIPATTERNS_HITBOXCOMPONENT_H
#define ANTIPATTERNS_HITBOXCOMPONENT_H


#include <SFML/Graphics.hpp>

class HitboxComponent {
public:
    HitboxComponent(sf::Sprite& sprite, float width, float height, float offset_x, float offset_y);
    ~HitboxComponent();

    void Update();
    void Render(sf::RenderTarget& target);

    void SetPosition(const sf::Vector2f& position);
    void ChangeSprite(sf::Sprite& sprite);

    bool CheckCollision(const sf::FloatRect& other);
private:
    sf::RectangleShape _hitbox;
    sf::Sprite* _sprite;
    sf::Vector2f _offset;
};


#endif //ANTIPATTERNS_HITBOXCOMPONENT_H
