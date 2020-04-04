//
// Created by dmitry on 4/1/20.
//

#include "HitboxComponent.h"
#include "iostream"

HitboxComponent::HitboxComponent(sf::Sprite &sprite, float width, float height, float offset_x, float offset_y)
        : _sprite(&sprite), _offset(offset_x, offset_y) {
    _hitbox.setPosition(_sprite->getPosition().x + offset_x, _sprite->getPosition().y + offset_y);
    _hitbox.setSize(sf::Vector2f(width, height));
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

void HitboxComponent::ChangeSprite(sf::Sprite &sprite) {
    _sprite = &sprite;
}


