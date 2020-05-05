//
// Created by dmitry on 4/2/20.
//

#include "Rat.h"


Rat::Rat(sf::Texture &texture_sheet, const std::map<std::string, Json::Node>& settings) {
    Creature::InitPhysicsComponent(settings.at("physics_component").AsMap());
    Creature::InitGraphicsComponent(texture_sheet, settings.at("graphics_component").AsMap());
    Creature::InitHitboxComponent(settings.at("hitbox_component").AsMap());
    Creature::InitAttributeComponent(settings.at("attribute_component").AsMap());
    Creature::InitExpComp(1);
}

Rat::Rat(const Rat &other) : Enemy(other) {
    std::cout << "rat copied" << std::endl;
}


void Rat::Update(float time_elapsed) {
    phys_comp_->Update(time_elapsed);
    /* here we use GetMovementState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    hitbox_comp_->Update();
}

void Rat::Render(sf::RenderTarget &target) const {
    target.draw(sprite_);
    hitbox_comp_->Render(target);
}


void Rat::UpdateAnimations(float time_elapsed) {
    Creature::UpdateMoveAnimations(time_elapsed);
}

std::unique_ptr<Enemy> Rat::Clone() const {
    return std::make_unique<Rat>(*this);
}





