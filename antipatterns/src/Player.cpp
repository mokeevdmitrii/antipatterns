//
// Created by dmitry on 3/30/20.
//

#include "Player.h"


Player::Player(sf::Vector2f position, const sf::Texture &texture_sheet, const std::string &file_name) {
    const std::map<std::string, Json::Node> settings = Json::Load(file_name).GetRoot().AsMap();
    Creature::InitPhysicsComponent(settings.at("physics_component").AsMap());
    Creature::InitGraphicsComponent(texture_sheet, settings.at("graphics_component").AsMap());
    Creature::InitHitboxComponent(settings.at("hitbox_component").AsMap());
    Creature::InitAttributeComponent(settings.at("attribute_component").AsMap());
    Creature::SetPosition(position);
}

Player::~Player() {

}

/* overrided functions */

void Player::Update(float time_elapsed) {
    phys_comp_->Update(time_elapsed);
    /* here we use GetMovementState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    hitbox_comp_->Update();
}

void Player::Render(sf::RenderTarget &target) const {
    target.draw(sprite_);
    hitbox_comp_->Render(target);
}

/* initializers */


void Player::UpdateAnimations(float time_elapsed) {
    MovementState state = phys_comp_->GetMovementState();
    if (state == MovementState::IDLE) {
        //std::cout << "idle" << std::endl;
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
        //std::cout << "moving" << std::endl;
        if (state == MOVING_DOWN) {
            graph_comp_->Play("MOVING_DOWN", time_elapsed, phys_comp_->GetVelocity().y / phys_comp_->GetMaxVelocity());
        } else if (state == MOVING_UP) {
            graph_comp_->Play("MOVING_UP", time_elapsed, phys_comp_->GetVelocity().y / phys_comp_->GetMaxVelocity());
        } else if (state == MOVING_LEFT) {
            graph_comp_->Play("MOVING_LEFT", time_elapsed, phys_comp_->GetVelocity().x / phys_comp_->GetMaxVelocity());
        } else if (state == MOVING_RIGHT) {
            graph_comp_->Play("MOVING_RIGHT", time_elapsed, phys_comp_->GetVelocity().x / phys_comp_->GetMaxVelocity());
        }
    }
}








