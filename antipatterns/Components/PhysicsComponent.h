//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_PHYSICSCOMPONENT_H
#define ANTIPATTERNS_PHYSICSCOMPONENT_H


#include "../Resources/GraphicsSettings.h"


enum MovementState {
    IDLE,
    MOVING,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class PhysicsComponent {
public:
    PhysicsComponent(sf::Sprite &sprite, float max_velocity = 0,
                     float acceleration = 0, float deceleration = 0);

    ~PhysicsComponent();

    /* getters */
    float GetMaxVelocity() const;
    sf::Vector2f GetVelocity() const;
    bool GetState(MovementState state) const;

    /* modifiers */
    /* for collisions in future */
    void Stop();
    void StopAxisMoveX();
    void StopAxisMoveY();

    /* functions */
    void Accelerate(float time_elapsed, const sf::Vector2f &_direction);
    void Update(float time_elapsed);

private:
    sf::Sprite &_sprite;

    sf::Vector2f _velocity;

    float _max_velocity;
    float _acceleration;
    float _deceleration;
};


#endif //ANTIPATTERNS_PHYSICSCOMPONENT_H
