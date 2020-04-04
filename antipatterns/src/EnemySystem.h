//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ENEMYSYSTEM_H
#define ANTIPATTERNS_ENEMYSYSTEM_H

#include "../Enemies/EnemySpawner.h"
#include "../Enemies/Rat.h"

class EnemySystem {
public:
    EnemySystem();

    ~EnemySystem();

    void LoadUniqueEnemies(const std::string& file_name);
    void LoadEnemies(const std::string& file_name);

    /* add and create will be private with other signature */
    void AddEnemy(std::unique_ptr<Enemy> enemy);
    void CreateEnemy(int index, const sf::Vector2f& pos, int level);

    void Update(float time_elapsed);

    void Render(sf::RenderTarget& target);
private:
    std::list<std::unique_ptr<Enemy>> _active_enemies;
    std::list<std::unique_ptr<Enemy>> _dead_enemies;
    std::vector<std::unique_ptr<Enemy>> _unique_enemies;
};


#endif //ANTIPATTERNS_ENEMYSYSTEM_H
