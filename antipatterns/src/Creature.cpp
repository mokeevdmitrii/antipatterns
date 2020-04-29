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
    _sprite = other._sprite;
    _phys_comp = std::make_unique<PhysicsComponent>(*other._phys_comp);
    _graph_comp = std::make_unique<GraphicsComponent>(*other._graph_comp);
    _attribute_comp = std::make_unique<AttributeComponent>(*other._attribute_comp);
    _hitbox_comp = std::make_unique<HitboxComponent>(*other._hitbox_comp);
    _phys_comp->UpdateCopy(_sprite);
    _graph_comp->UpdateCopy(_sprite);
    _hitbox_comp->UpdateCopy(_sprite);
    return *this;
}


Creature::Creature(const Creature &other) {
    *this = other;
}

void Creature::SetPosition(const sf::Vector2f &position) {
    if (_hitbox_comp != nullptr) {
        _hitbox_comp->SetPosition(position);
    } else {
        _sprite.setPosition(position);
    }
}

void Creature::Move(const float time_elapsed, const sf::Vector2f &direction) {
    if (this->_phys_comp != nullptr) {
        _phys_comp->Accelerate(time_elapsed, direction);
    }
}


void Creature::SetTexture(sf::Texture& texture) {
    _sprite.setTexture(texture);
}

void Creature::InitPhysicsComponent(const std::map<std::string, Json::Node> &settings) {
    _phys_comp = std::make_unique<PhysicsComponent>(_sprite, settings);
}

void Creature::InitGraphicsComponent(sf::Texture& texture_sheet, const std::map<std::string, Json::Node> &settings) {
    _graph_comp = std::make_unique<GraphicsComponent>(_sprite, texture_sheet, settings);
}

void Creature::InitHitboxComponent(const std::map<std::string, Json::Node> &settings) {
    _hitbox_comp = std::make_unique<HitboxComponent>(_sprite, settings);
}

void Creature::InitAttributeComponent(const std::map<std::string, Json::Node> &settings) {
    _attribute_comp = std::make_unique<AttributeComponent>(settings);
}

sf::Vector2f Creature::GetPosition() const {
    return _hitbox_comp != nullptr ?  _hitbox_comp->GetPosition() : _sprite.getPosition();
}











