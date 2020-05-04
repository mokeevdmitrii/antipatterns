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

void Creature::SetTexture(sf::Texture &texture) {
    sprite_.setTexture(texture);
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


void Creature::InitPhysicsComponent(const std::map<std::string, Json::Node> &settings) {
    phys_comp_ = std::make_unique<PhysicsComponent>(sprite_, settings);
}

void Creature::InitGraphicsComponent(const sf::Texture &texture_sheet, const std::map<std::string, Json::Node> &settings) {
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
    sf::Vector2f position = GetHitbox().getPosition();
    for (size_t point_index = 0; point_index < 4; ++point_index) {
        sf::Vector2f curr_point = other_hitbox.getPoint(point_index);
        curr_point.x += position.x, curr_point.y += position.y;
        if (!hitbox_rect.contains(curr_point)) {
            return false;
        }
    }
    return true;
}

bool Creature::ContainedIn(const sf::RectangleShape &other_hitbox) const {
    sf::FloatRect other_rect = other_hitbox.getGlobalBounds();
    sf::RectangleShape hitbox = GetHitbox();
    sf::Vector2f position = hitbox.getPosition();
    for (size_t point_index = 0; point_index < 4; ++point_index) {
        sf::Vector2f curr_point = hitbox.getPoint(point_index);
        curr_point.x += position.x, curr_point.y += position.y;
        if (!other_rect.contains(curr_point)) {
            return false;
        }
    }
    return true;
}

void Creature::UpdateMoveAnimations(float time_elapsed) {
    MovementState state = phys_comp_->GetMovementState();
    if (state == MovementState::IDLE) {
        MovementState last_direction = phys_comp_->GetLastMoveDirection();
        if (last_direction == MovementState::IDLE || last_direction == MovementState::MOVING_DOWN) {
            graph_comp_->Play("IDLE_DOWN", time_elapsed);
        } else if (last_direction == MovementState::MOVING_UP) {
            graph_comp_->Play("IDLE_UP", time_elapsed);
        } else if (last_direction == MovementState::MOVING_LEFT) {
            graph_comp_->Play("IDLE_LEFT", time_elapsed);
        } else if (last_direction == MovementState::MOVING_RIGHT) {
            graph_comp_->Play("IDLE_RIGHT", time_elapsed);
        }
    } else {
        if (state == MovementState::MOVING_DOWN) {
            graph_comp_->Play("MOVING_DOWN", time_elapsed, std::abs(phys_comp_->GetVelocity().y) / phys_comp_->GetMaxVelocity());
        } else if (state == MovementState::MOVING_UP) {
            graph_comp_->Play("MOVING_UP", time_elapsed, std::abs(phys_comp_->GetVelocity().y) / phys_comp_->GetMaxVelocity());
        } else if (state == MovementState::MOVING_LEFT) {
            graph_comp_->Play("MOVING_LEFT", time_elapsed, std::abs(phys_comp_->GetVelocity().x) / phys_comp_->GetMaxVelocity());
        } else if (state == MovementState::MOVING_RIGHT) {
            graph_comp_->Play("MOVING_RIGHT", time_elapsed, std::abs(phys_comp_->GetVelocity().x) / phys_comp_->GetMaxVelocity());
        }
    }
}

float Creature::GetDistance(const Creature &other) const {
    sf::Vector2f pos = GetPosition(), other_pos = other.GetPosition();
    return Utility::GetDistance(pos, other_pos);
}













