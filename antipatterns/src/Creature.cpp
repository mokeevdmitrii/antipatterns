//
// Created by dmitry on 3/28/20.
//

#include "Creature.h"

Creature::Creature() {

}

Creature::~Creature() {

}


void Creature::SetPosition(const sf::Vector2f &position) {
    _sprite.setPosition(position);
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
    _phys_comp = std::make_shared<PhysicsComponent>(_sprite, max_velocity, acceleration, deceleration);
}

void Creature::InitGraphicsComponent(sf::Texture& texture_sheet) {
    _graph_comp = std::make_shared<GraphicsComponent>(_sprite, texture_sheet);
}

void Creature::InitHitboxComponent(sf::Sprite &sprite, float width, float height, float offset_x, float offset_y) {
    _hitbox_comp = std::make_shared<HitboxComponent>(_sprite, width, height, offset_x, offset_y);
}







