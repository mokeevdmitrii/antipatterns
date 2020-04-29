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
    HitboxComponent(const HitboxComponent& other) = default;
    HitboxComponent& operator = (const HitboxComponent& other) = default;
    ~HitboxComponent();

    /* initializer */
    void LoadFromMap(const std::map<std::string, Json::Node>& settings);

    void Update();
    void Render(sf::RenderTarget& target) const;

    void SetPosition(const sf::Vector2f& position);
    void UpdateCopy(sf::Sprite& sprite);

    bool CheckCollision(const sf::FloatRect& other) const;
    /* getters */
    sf::Vector2f GetPosition() const;
private:
    sf::RectangleShape hitbox_;
    sf::Sprite* sprite_;
    sf::Vector2f offset_;
};


#endif //ANTIPATTERNS_HITBOXCOMPONENT_H
