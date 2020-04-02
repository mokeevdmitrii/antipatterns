//
// Created by dmitry on 3/30/20.
//

#include "Player.h"

Player::Player(const sf::Vector2f position, sf::Texture &texture_sheet) {
    Creature::SetPosition(position);
    Creature::InitPhysicsComponent(100.f, 2000.f, 1000.f);
    Creature::InitGraphicsComponent(texture_sheet);
    Creature::InitHitboxComponent(_sprite, 32,  48, 0, 0);
    /* init animations IS NOT READY */
    InitAnimations();

}

Player::~Player() {

}

/* overrided functions */

void Player::Update(float time_elapsed) {
    _phys_comp->Update(time_elapsed);
    /* here we use GetState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    _hitbox_comp->Update();
}

void Player::Render(sf::RenderTarget &target) {
    target.draw(_sprite);
    _hitbox_comp->Render(target);
}

/* initializers */

void Player::InitAnimations() {
    _graph_comp->AddAnimation("PLAYER_IDLE", 0.f, 0, 0, 0, 0, sf::Vector2i(32, 48));
}

void Player::UpdateAnimations(float time_elapsed) {
    _graph_comp->Play("PLAYER_IDLE", time_elapsed);
}




