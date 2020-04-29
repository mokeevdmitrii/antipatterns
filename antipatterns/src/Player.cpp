//
// Created by dmitry on 3/30/20.
//

#include "Player.h"


Player::Player(sf::Vector2f position, sf::Texture &texture_sheet, const std::string &file_name,
               std::shared_ptr<std::unordered_map<std::string, int>> keybindings) : keybindings_(
        std::move(keybindings)) {
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
    UpdateInput(time_elapsed);
    phys_comp_->Update(time_elapsed);
    /* here we use GetState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    hitbox_comp_->Update();
}

void Player::Render(sf::RenderTarget &target) const {
    target.draw(sprite_);
    hitbox_comp_->Render(target);
}

/* initializers */


void Player::UpdateInput(float time_elapsed) {
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_LEFT")))) {
        Move(time_elapsed, sf::Vector2f(-1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_DOWN")))) {
        Move(time_elapsed, sf::Vector2f(0.f, 1.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_RIGHT")))) {
        Move(time_elapsed, sf::Vector2f(1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_UP")))) {
        Move(time_elapsed, sf::Vector2f(0.f, -1.f));
    }
}

void Player::UpdateAnimations(float time_elapsed) {
    graph_comp_->Play("PLAYER_IDLE", time_elapsed);
}








