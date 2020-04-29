//
// Created by dmitry on 4/1/20.
//

#include "HitboxComponent.h"
#include "iostream"

HitboxComponent::HitboxComponent(sf::Sprite &sprite, const std::map<std::string, Json::Node> &settings)
        : sprite_(&sprite) {
    LoadFromMap(settings);
    hitbox_.setPosition(sprite_->getPosition().x + offset_.x, sprite_->getPosition().y + offset_.y);
    hitbox_.setFillColor(sf::Color::Transparent);
    hitbox_.setOutlineColor(sf::Color::Blue);
    hitbox_.setOutlineThickness(1);
}

HitboxComponent::~HitboxComponent() {

}

void HitboxComponent::Update() {
    hitbox_.setPosition(sprite_->getPosition().x + offset_.x, sprite_->getPosition().y + offset_.y);
}

void HitboxComponent::Render(sf::RenderTarget &target) const {
    target.draw(hitbox_);
}

bool HitboxComponent::CheckCollision(const sf::FloatRect &other) const {
    return hitbox_.getGlobalBounds().intersects(other);
}

void HitboxComponent::SetPosition(const sf::Vector2f& position) {
    hitbox_.setPosition(position);
    sprite_->setPosition(position.x - offset_.x, position.y - offset_.y);
}

void HitboxComponent::UpdateCopy(sf::Sprite &sprite) {
    sprite_ = &sprite;
}

void HitboxComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    float width = static_cast<float>(settings.at("width").AsDouble());
    float height = static_cast<float>(settings.at("height").AsDouble());
    float offset_x = static_cast<float>(settings.at("offset_x").AsDouble());
    float offset_y = static_cast<float>(settings.at("offset_y").AsDouble());
    hitbox_.setSize(sf::Vector2f(width, height));
    offset_ = sf::Vector2f(offset_x, offset_y);
}

sf::Vector2f HitboxComponent::GetPosition() const {
    return hitbox_.getPosition();
}




