//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_PHYSICSCOMPONENT_H
#define ANTIPATTERNS_PHYSICSCOMPONENT_H


#include "../Resources/GraphicsSettings.h"
#include "../Resources/Json.h"


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
    PhysicsComponent(sf::Sprite &sprite, const std::map<std::string, Json::Node> &settings);

    /* initializer */
    void LoadFromMap(const std::map<std::string, Json::Node>& settings);

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
    void UpdateCopy(sf::Sprite &sprite);

private:
    sf::Sprite *_sprite;

    sf::Vector2f _velocity;

    float _max_velocity;
    float _acceleration;
    float _deceleration;
};


#endif //ANTIPATTERNS_PHYSICSCOMPONENT_H
