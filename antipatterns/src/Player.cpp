//
// Created by dmitry on 3/30/20.
//

#include "Player.h"

Player::Player(const sf::Vector2f position, std::shared_ptr<sf::Texture> texture)  {
    Creature::SetPosition(position);
    Creature::SetTexture(std::move(texture));
    InitComponents();
}

Player::~Player() {

}

/* overrided functions */

void Player::Update(float time_elapsed) {
    _phys_comp->Update(time_elapsed);
}

void Player::Render(const std::shared_ptr<sf::RenderTarget> &target) {
    target->draw(_sprite);
}

/* initializers */

void Player::InitComponents() {
    InitPhysicsComponent(100.f, 3200.f, 2000.f);
}



