//
// Created by dmitry on 4/2/20.
//

#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Texture &texture_sheet, const std::map<std::string, Json::Node> &settings,
                           std::shared_ptr<Enemy> prototype) : prototype_(std::move(prototype)) {
    Creature::InitPhysicsComponent(settings.at("physics_component").AsMap());
    Creature::InitGraphicsComponent(texture_sheet, settings.at("graphics_component").AsMap());
    Creature::InitHitboxComponent(settings.at("hitbox_component").AsMap());
    Creature::InitAttributeComponent(settings.at("attribute_component").AsMap());
}

EnemySpawner::EnemySpawner(const EnemySpawner &other) : Enemy(other) {
    /* spawned enemies in EnemySpawner prototype is guaranteed to be empty! */
    std::cout << "EnemySpawner copied" << std::endl;
    spawn_clock_.restart();
}

void EnemySpawner::Update(float time_elapsed) {
    phys_comp_->Update(time_elapsed);
    /* here we use GetMovementState from PhysicsComponent and play animations */
    UpdateAnimations(time_elapsed);
    /* here animations end */
    hitbox_comp_->Update();
    /* create an enemy */
    if (!cloned && spawn_clock_.getElapsedTime().asSeconds() >= 5) {
        CreateEnemy(attribute_comp_->GetLevel());
        cloned = true;
    }
    /* update all spawned enemies */
    for (auto& enemy : spawned_enemies_) {
        enemy->Update(time_elapsed);
    }
}

void EnemySpawner::UpdatePlayer(float time_elapsed, const std::shared_ptr<Creature> &player) {
    //Enemy::UpdatePlayer(time_elapsed, player);
    for (auto &enemy : spawned_enemies_) {
        enemy->UpdatePlayer(time_elapsed, player);
    }
}

void EnemySpawner::Render(sf::RenderTarget &target) const {
    target.draw(sprite_);
    hitbox_comp_->Render(target);
    for (auto& enemy : spawned_enemies_) {
        enemy->Render(target);
    }
}

std::unique_ptr<Enemy> EnemySpawner::Clone() const {
    return std::make_unique<EnemySpawner>(*this);
}

void EnemySpawner::CreateEnemy(int level) {
    std::unique_ptr<Enemy> clone = prototype_->Clone();
    /* further : generate new position for an enemy */
    clone->SetPosition(sf::Vector2f(GetPosition().x + 20, GetPosition().y - 30));
    clone->GenerateAttributes(level);
    spawned_enemies_.push_back(std::move(clone));
}


void EnemySpawner::SetPrototype(std::shared_ptr<Enemy> prototype) {
    prototype_ = std::move(prototype);
}



void EnemySpawner::UpdateAnimations(float time_elapsed) {
    Creature::UpdateMoveAnimations(time_elapsed);
}








