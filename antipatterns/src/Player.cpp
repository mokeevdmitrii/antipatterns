//
// Created by dmitry on 3/30/20.
//

#include "Player.h"


Player::Player(const sf::Vector2f position, sf::Texture &texture_sheet, const std::string &file_name) {
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
    _phys_comp->Update(time_elapsed);
    /* here we use GetState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    _hitbox_comp->Update();
}

void Player::Render(sf::RenderTarget &target) const {
    target.draw(_sprite);
    _hitbox_comp->Render(target);
}

/* initializers */

//void Player::InitAnimations() {
//    _graph_comp->AddAnimation("PLAYER_IDLE", 0.f, 0, 0, 0, 0, sf::Vector2i(32, 48));
//}

void Player::UpdateAnimations(float time_elapsed) {
    _graph_comp->Play("PLAYER_IDLE", time_elapsed);
}




