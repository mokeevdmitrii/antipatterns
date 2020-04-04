//
// Created by dmitry on 3/31/20.
//

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(sf::Sprite &sprite, const std::map<std::string, Json::Node> &settings) :
        _sprite(&sprite)  {
    LoadFromMap(settings);
}

void PhysicsComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    _max_velocity = static_cast<float>(settings.at("max_velocity").AsDouble());
    _acceleration = static_cast<float>(settings.at("acceleration").AsDouble());
    _deceleration = static_cast<float>(settings.at("deceleration").AsDouble());
}


PhysicsComponent::~PhysicsComponent() {

}

/* getters */
float PhysicsComponent::GetMaxVelocity() const {
    return _max_velocity;
}

sf::Vector2f PhysicsComponent::GetVelocity() const {
    return _velocity;
}

bool PhysicsComponent::GetState(MovementState state) const {
    switch (state) {
        case IDLE:
            return _velocity.x == _velocity.y == 0;
        case MOVING:
            return _velocity.x != 0 || _velocity.y != 0;
        case MOVING_LEFT:
            return _velocity.x < 0 && std::abs(_velocity.x) >= std::abs(_velocity.y);
        case MOVING_RIGHT:
            return _velocity.x > 0 && std::abs(_velocity.x) >= std::abs(_velocity.y);
        case MOVING_UP:
            return _velocity.y < 0 && std::abs(_velocity.x) < std::abs(_velocity.y);
        case MOVING_DOWN:
            return _velocity.y > 0 && std::abs(_velocity.x) < std::abs(_velocity.y);
        default:
            throw std::runtime_error("CASE NOT HANDLED");
    }
}

/* modifiers */
void PhysicsComponent::Stop() {
    _velocity.x = _velocity.y = 0;
}

void PhysicsComponent::StopAxisMoveX() {
    _velocity.x = 0;
}

void PhysicsComponent::StopAxisMoveY() {
    _velocity.y = 0;
}

/* functions */
void PhysicsComponent::Accelerate(const float time_elapsed, const sf::Vector2f& direction) {
    _velocity.x += _acceleration * direction.x * time_elapsed;
    _velocity.y += _acceleration * direction.y * time_elapsed;
}

void PhysicsComponent::Update(const float time_elapsed) {
    /* написать здесь нормальную проверку на текущую скорость */
    float abs_v = sqrtf(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
    float cos_a = _velocity.x / abs_v;
    float sin_a = _velocity.y / abs_v;
    if (abs_v > _max_velocity) {
        _velocity.x = _max_velocity * cos_a;
        _velocity.y = _max_velocity * sin_a;
    }
    if (_velocity.x != 0) {
        _velocity.x -= _deceleration * cos_a * time_elapsed;
        if (_velocity.x * cos_a < 0) {
            _velocity.x = 0;
        }
    }
    if (_velocity.y != 0) {
        _velocity.y -= _deceleration * sin_a * time_elapsed;
        if (_velocity.y * sin_a < 0) {
            _velocity.y = 0;
        }
    }
    _velocity.x = _velocity.x;
    _velocity.y = _velocity.y;
    _sprite->move(_velocity * time_elapsed);
}

void PhysicsComponent::UpdateCopy(sf::Sprite &sprite) {
    _sprite = &sprite;
}


