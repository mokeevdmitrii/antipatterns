//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ENEMYSYSTEM_H
#define ANTIPATTERNS_ENEMYSYSTEM_H

#include "EnemySpawner.h"
#include "../Enemies/Rat.h"

class EnemySystem {
public:
    EnemySystem() {

    }

    /* temp function */
    void AddEnemy(std::unique_ptr<Enemy> enemy) {
        _unique_enemies.push_back(std::move(enemy));
    }

    void CreateEnemy(int index, sf::Vector2<float> pos, int level) {
        _active_enemies.push_back(_unique_enemies.at(index)->Clone(pos, level));
    }

    void Update(float time_elapsed) {
        for (auto& active_enemy : _active_enemies) {
            active_enemy->Update(time_elapsed);
        }
    }

    void Render(sf::RenderTarget& target) {
        for (auto& active_enemy : _active_enemies) {
            active_enemy->Render(target);
        }
    }
private:
    std::list<std::unique_ptr<Enemy>> _active_enemies;
    std::list<std::unique_ptr<Enemy>> _dead_enemies;
    std::vector<std::unique_ptr<Enemy>> _unique_enemies;
};


#endif //ANTIPATTERNS_ENEMYSYSTEM_H
