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


void Creature::SetTexture(std::shared_ptr<sf::Texture> texture) {
    _texture = std::move(texture);
    _sprite.setTexture(*_texture);
}

void Creature::InitPhysicsComponent(float max_velocity, float acceleration, float deceleration) {
    _phys_comp = std::make_unique<PhysicsComponent>(_sprite, max_velocity, acceleration, deceleration);
}

void Creature::InitGraphicsComponent() {

}







