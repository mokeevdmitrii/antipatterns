//
// Created by dmitry on 3/28/20.
//

#include "Creature.h"

Creature::Creature() {

}

Creature::~Creature() {

}

Creature &Creature::operator=(const Creature &other) {
    if (&other == this) {
        return *this;
    }
    std::cout << "creature copied (operator)" << std::endl;
    sprite_ = other.sprite_;
    phys_comp_ = std::make_unique<PhysicsComponent>(*other.phys_comp_);
    graph_comp_ = std::make_unique<GraphicsComponent>(*other.graph_comp_);
    attribute_comp_ = std::make_unique<AttributeComponent>(*other.attribute_comp_);
    hitbox_comp_ = std::make_unique<HitboxComponent>(*other.hitbox_comp_);
    phys_comp_->UpdateCopy(sprite_);
    graph_comp_->UpdateCopy(sprite_);
    hitbox_comp_->UpdateCopy(sprite_);
    return *this;
}


Creature::Creature(const Creature &other) {
    *this = other;
}

void Creature::SetPosition(const sf::Vector2f &position) {
    if (hitbox_comp_ != nullptr) {
        hitbox_comp_->SetPosition(position);
    } else {
        sprite_.setPosition(position);
    }
}

void Creature::Move(const float time_elapsed, const sf::Vector2f &direction) {
    if (this->phys_comp_ != nullptr) {
        phys_comp_->Accelerate(time_elapsed, direction);
    }
}


void Creature::SetTexture(sf::Texture& texture) {
    sprite_.setTexture(texture);
}

void Creature::InitPhysicsComponent(const std::map<std::string, Json::Node> &settings) {
    phys_comp_ = std::make_unique<PhysicsComponent>(sprite_, settings);
}

void Creature::InitGraphicsComponent(sf::Texture& texture_sheet, const std::map<std::string, Json::Node> &settings) {
    graph_comp_ = std::make_unique<GraphicsComponent>(sprite_, texture_sheet, settings);
}

void Creature::InitHitboxComponent(const std::map<std::string, Json::Node> &settings) {
    hitbox_comp_ = std::make_unique<HitboxComponent>(sprite_, settings);
}

void Creature::InitAttributeComponent(const std::map<std::string, Json::Node> &settings) {
    attribute_comp_ = std::make_unique<AttributeComponent>(settings);
}

sf::Vector2f Creature::GetPosition() const {
    return hitbox_comp_ != nullptr ? hitbox_comp_->GetPosition() : sprite_.getPosition();
}

void Creature::SetPossibleMoveDirections(PossibleDirections directions) {
    if (phys_comp_ != nullptr) {
        phys_comp_->SetPossibleMoveDirections(directions);
    }
}

sf::RectangleShape Creature::GetHitbox() const {
    if (hitbox_comp_ != nullptr) {
        return hitbox_comp_->GetHitbox();
    }
    sf::FloatRect bounds = sprite_.getGlobalBounds();
    auto result = sf::RectangleShape(sf::Vector2f(bounds.width, bounds.height));
    result.setPosition(sprite_.getPosition());
    return result;
}

bool Creature::Intersects(const sf::RectangleShape &other_hitbox) const {
    return GetHitbox().getGlobalBounds().intersects(other_hitbox.getGlobalBounds());
}

bool Creature::Contains(const sf::RectangleShape &other_hitbox) const {
    sf::FloatRect hitbox_rect = sf::FloatRect(GetHitbox().getPosition(), GetHitbox().getSize());
    for (size_t point_index = 0; point_index < 4; ++point_index) {
        if (!hitbox_rect.contains(other_hitbox.getPoint(point_index))) {
            return false;
        }
    }
    return true;
}

bool Creature::Contained(const sf::RectangleShape &other_hitbox) const {
    sf::FloatRect other_rect = other_hitbox.getGlobalBounds();
    sf::RectangleShape hitbox = GetHitbox();
    for (size_t point_index = 0; point_index < 4; ++point_index) {
        if (!other_rect.contains(hitbox.getPoint(point_index))) {
            return false;
        }
    }
    return true;
}













