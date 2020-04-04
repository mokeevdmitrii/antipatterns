//
// Created by dmitry on 3/28/20.
//

#include "Creature.h"

Creature::Creature() {

}

Creature::~Creature() {

}

Creature::Creature(const Creature &other) {
    std::cout << "creature copied" << std::endl;
    _sprite = other._sprite;
    _phys_comp = std::make_unique<PhysicsComponent>(*other._phys_comp);
    _graph_comp = std::make_unique<GraphicsComponent>(*other._graph_comp);
    _attribute_comp = std::make_unique<AttributeComponent>(*other._attribute_comp);
    _hitbox_comp = std::make_unique<HitboxComponent>(*other._hitbox_comp);
    _phys_comp->ChangeSprite(_sprite);
    _graph_comp->ChangeSprite(_sprite);
    _hitbox_comp->ChangeSprite(_sprite);
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

void Creature::InitPhysicsComponent(float max_velocity, float acceleration, float deceleration) {
    _phys_comp = std::make_unique<PhysicsComponent>(_sprite, max_velocity, acceleration, deceleration);
}

void Creature::InitGraphicsComponent(sf::Texture& texture_sheet) {
    _graph_comp = std::make_unique<GraphicsComponent>(_sprite, texture_sheet);
}

void Creature::InitHitboxComponent(sf::Sprite &sprite, float width, float height, float offset_x, float offset_y) {
    _hitbox_comp = std::make_unique<HitboxComponent>(_sprite, width, height, offset_x, offset_y);
}

void Creature::InitAttributeComponent(int level) {
    _attribute_comp = std::make_unique<AttributeComponent>(level);
}










