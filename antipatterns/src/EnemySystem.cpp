//
// Created by dmitry on 4/2/20.
//

#include "EnemySystem.h"

/* constructors and destructors */

EnemySystem::EnemySystem() {

}

EnemySystem::~EnemySystem() {

}

void EnemySystem::LoadUniqueEnemies(const std::string &file_name) {

}

void EnemySystem::LoadEnemies(const std::string &file_name) {

}

void EnemySystem::AddEnemy(std::unique_ptr<Enemy> enemy) {
    _unique_enemies.push_back(std::move(enemy));
}

void EnemySystem::CreateEnemy(int index, const sf::Vector2f& pos, int level) {
    std::unique_ptr<Enemy> _clone = _unique_enemies.at(index)->Clone();
    _clone->SetPosition(pos);
    _clone->GenerateAttributes(level);
    _active_enemies.push_back(std::move(_clone));
}

void EnemySystem::Update(float time_elapsed) {
    for (auto& active_enemy : _active_enemies) {
        active_enemy->Update(time_elapsed);
    }
}

void EnemySystem::Render(sf::RenderTarget &target) {
    for (auto& active_enemy : _active_enemies) {
        active_enemy->Render(target);
    }
}






