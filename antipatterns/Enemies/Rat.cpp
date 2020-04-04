//
// Created by dmitry on 4/2/20.
//

#include "Rat.h"


Rat::Rat(const sf::Vector2f &position, sf::Texture &texture_sheet) {
    Creature::InitPhysicsComponent(50.f, 1000.f, 600.f);
    Creature::InitGraphicsComponent(texture_sheet);
    Creature::InitHitboxComponent(_sprite, 32, 48, 0, 0);
    Creature::InitAttributeComponent(2);

    Creature::SetPosition(position);
    InitAnimations();
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

void Rat::InitAnimations() {
    _graph_comp->AddAnimation("PLAYER_IDLE", 0.f, 0, 0, 0, 0, sf::Vector2i(32, 48));
}

void Rat::UpdateAnimations(float time_elapsed) {
    _graph_comp->Play("PLAYER_IDLE", time_elapsed);
}

std::unique_ptr<Enemy> Rat::Clone() {
    return std::make_unique<Rat>(*this);
}





