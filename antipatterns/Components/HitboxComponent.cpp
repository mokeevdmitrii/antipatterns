//
// Created by dmitry on 4/1/20.
//

#include "HitboxComponent.h"
#include "iostream"

HitboxComponent::HitboxComponent(sf::Sprite &sprite, const std::map<std::string, Json::Node> &settings)
        : _sprite(&sprite) {
    LoadFromMap(settings);
    _hitbox.setPosition(_sprite->getPosition().x + _offset.x, _sprite->getPosition().y + _offset.y);
    _hitbox.setFillColor(sf::Color::Transparent);
    _hitbox.setOutlineColor(sf::Color::Blue);
    _hitbox.setOutlineThickness(1);
}

HitboxComponent::~HitboxComponent() {

}

void HitboxComponent::Update() {
    _hitbox.setPosition(_sprite->getPosition().x + _offset.x, _sprite->getPosition().y + _offset.y);
}

void HitboxComponent::Render(sf::RenderTarget &target) {
    target.draw(_hitbox);
}

bool HitboxComponent::CheckCollision(const sf::FloatRect &other) {
    return _hitbox.getGlobalBounds().intersects(other);
}

void HitboxComponent::SetPosition(const sf::Vector2f& position) {
    _hitbox.setPosition(position);
    _sprite->setPosition(position.x - _offset.x, position.y - _offset.y);
}

void HitboxComponent::UpdateCopy(sf::Sprite &sprite) {
    _sprite = &sprite;
}

void HitboxComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    float width = static_cast<float>(settings.at("width").AsDouble());
    float height = static_cast<float>(settings.at("height").AsDouble());
    float offset_x = static_cast<float>(settings.at("offset_x").AsDouble());
    float offset_y = static_cast<float>(settings.at("offset_y").AsDouble());
    _hitbox.setSize(sf::Vector2f(width, height));
    _offset = sf::Vector2f(offset_x, offset_y);
}




