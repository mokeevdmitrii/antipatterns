//
// Created by dmitry on 4/2/20.
//

#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Texture &texture_sheet, const std::map<std::string, Json::Node> &settings,
                           std::shared_ptr<Enemy> prototype) : _prototype(std::move(prototype)) {
    Creature::InitPhysicsComponent(settings.at("physics_component").AsMap());
    Creature::InitGraphicsComponent(texture_sheet, settings.at("graphics_component").AsMap());
    Creature::InitHitboxComponent(settings.at("hitbox_component").AsMap());
    Creature::InitAttributeComponent(settings.at("attribute_component").AsMap());
}

EnemySpawner::EnemySpawner(const EnemySpawner &other) : Enemy(other) {
    /* spawned enemies in EnemySpawner prototype is guaranteed to be empty! */
    std::cout << "EnemySpawner copied" << std::endl;
    _spawn_clock.restart();
}

void EnemySpawner::Update(float time_elapsed) {
    _phys_comp->Update(time_elapsed);
    /* here we use GetState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    _hitbox_comp->Update();
    /* create an enemy */
    if (!cloned && _spawn_clock.getElapsedTime().asSeconds() >= 5) {
        CreateEnemy(_attribute_comp->GetLevel());
        cloned = true;
    }
    /* update all spawned enemies */
    for (auto& enemy : _spawned_enemies) {
        enemy->Update(time_elapsed);
    }
}

void EnemySpawner::Render(sf::RenderTarget &target) const {
    target.draw(_sprite);
    _hitbox_comp->Render(target);
    for (auto& enemy : _spawned_enemies) {
        enemy->Render(target);
    }
}

std::unique_ptr<Enemy> EnemySpawner::Clone() const {
    return std::make_unique<EnemySpawner>(*this);
}

void EnemySpawner::CreateEnemy(int level) {
    std::unique_ptr<Enemy> clone = _prototype->Clone();
    /* further : generate new position for an enemy */
    clone->SetPosition(sf::Vector2f(GetPosition().x + 20, GetPosition().y - 30));
    clone->GenerateAttributes(level);
    _spawned_enemies.push_back(std::move(clone));
}


void EnemySpawner::SetPrototype(std::shared_ptr<Enemy> prototype) {
    _prototype = std::move(prototype);
}



void EnemySpawner::UpdateAnimations(float time_elapsed) {
    _graph_comp->Play("PLAYER_IDLE", time_elapsed);
}






