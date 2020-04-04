//
// Created by dmitry on 4/2/20.
//

#include "Rat.h"


Rat::Rat(const sf::Vector2f &position, sf::Texture &texture_sheet, const std::map<std::string, Json::Node>& settings) {
    Creature::InitPhysicsComponent(settings.at("physics_component").AsMap());
    Creature::InitGraphicsComponent(texture_sheet, settings.at("graphics_component").AsMap());
    Creature::InitHitboxComponent(settings.at("hitbox_component").AsMap());
    Creature::InitAttributeComponent(settings.at("attribute_component").AsMap());

    Creature::SetPosition(position);
}

Rat::Rat(const Rat &other) : Enemy(other) {
    std::cout << "rat copied" << std::endl;
}


void Rat::Update(float time_elapsed) {
    _phys_comp->Update(time_elapsed);
    /* here we use GetState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    _hitbox_comp->Update();
}

void Rat::Render(sf::RenderTarget &target) {
    target.draw(_sprite);
    _hitbox_comp->Render(target);
}


void Rat::UpdateAnimations(float time_elapsed) {
    _graph_comp->Play("PLAYER_IDLE", time_elapsed);
}

std::unique_ptr<Enemy> Rat::Clone() {
    return std::make_unique<Rat>(*this);
}





