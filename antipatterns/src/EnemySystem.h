//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ENEMYSYSTEM_H
#define ANTIPATTERNS_ENEMYSYSTEM_H

#include "../Enemies/EnemySpawner.h"
#include "../Enemies/Rat.h"

struct EnemyParams {
    int _type{};
    int _level{1};
    int _type_to_spawn{-1};
};

class EnemySystem {
public:
    EnemySystem(std::unordered_map<std::string, sf::Texture> &textures, const std::string &enemies_settings_file,
                const std::string &enemies_location_file);

    ~EnemySystem();

    void LoadUniqueEnemies(const std::string& file_name);
    void LoadEnemies(const std::string& file_name);

    /* add and create will be private with other signature */
    void CreateEnemy(EnemyParams params, const sf::Vector2f &pos);

    void Update(float time_elapsed);

    void Render(sf::RenderTarget& target) const;
private:
    /* returns new random position on map for [x][y]-tile within the tile */
    /* implement later */
    //sf::Vector2f GeneratePosition(int x, int y);


    /* will think about possible use of these functions */
    void AddUniqueEnemy(std::shared_ptr<Enemy> enemy);

    std::list<std::unique_ptr<Enemy>> _active_enemies;
    std::list<std::unique_ptr<Enemy>> _dead_enemies;
    std::vector<std::shared_ptr<Enemy>> _unique_enemies;
    std::unordered_map<std::string, sf::Texture>& _textures;
    int _tile_size;
};


#endif //ANTIPATTERNS_ENEMYSYSTEM_H
