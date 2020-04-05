//
// Created by dmitry on 4/2/20.
//

#include "EnemySystem.h"

/* constructors and destructors */

EnemySystem::EnemySystem(std::unordered_map<std::string, sf::Texture> &textures,
                         const std::string &enemies_settings_file,
                         const std::string &enemies_location_file) : _textures(textures) {
    LoadUniqueEnemies(enemies_settings_file);
    LoadEnemies(enemies_location_file);
}

EnemySystem::~EnemySystem() {

}

void EnemySystem::LoadUniqueEnemies(const std::string &file_name) {
    /* загружает все виды врагов в вектор уникальных врагов */
    const std::map<std::string, Json::Node> enemy_settings = Json::Load(file_name).GetRoot().AsMap();
    _tile_size = static_cast<int>(enemy_settings.at("tile_size").AsDouble());
    /* index 0 */
    AddUniqueEnemy(std::make_shared<EnemySpawner>(_textures.at("PLAYER"), enemy_settings.at("EnemySpawner").AsMap()));
    /* index 1 will fix this ****-code later*/
    AddUniqueEnemy(std::make_shared<Rat>(_textures.at("PLAYER"), enemy_settings.at("Rat").AsMap()));
}

void EnemySystem::LoadEnemies(const std::string &file_name) {
    const std::vector<Json::Node> enemies_location = Json::Load(file_name).GetRoot().AsArray();
    for (int x = 0; x < enemies_location.size(); ++x) {
        const std::vector<Json::Node>& enemies_x = enemies_location[x].AsArray();
        for (int y = 0; y < enemies_x.size(); ++y) {
            const std::vector<Json::Node>& enemies_y = enemies_x[y].AsArray();
            if (enemies_y.empty()) {
                continue;
            }
            int enemy_type = static_cast<int>(enemies_y[0].AsDouble());
            int enemy_level = static_cast<int>(enemies_y[1].AsDouble());
            int enemy_type_to_spawn = -1;
            if (enemies_y.size() > 2) {
                enemy_type_to_spawn = static_cast<int>(enemies_y[2].AsDouble());
            }
            CreateEnemy({enemy_type, enemy_level, enemy_type_to_spawn}, sf::Vector2f(x * _tile_size, y * _tile_size));
        }
    }
}


void EnemySystem::CreateEnemy(EnemyParams params, const sf::Vector2f &pos) {
    std::unique_ptr<Enemy> clone = _unique_enemies.at(params._type)->Clone();
    clone->GenerateAttributes(params._level);
    /* if is a correct-defined spawner */
    if (params._type_to_spawn != -1) {
        auto& _spawner = dynamic_cast<EnemySpawner&>(*clone);
        _spawner.SetPrototype(_unique_enemies.at(params._type_to_spawn));
    }
    clone->SetPosition(pos);
    _active_enemies.push_back(std::move(clone));
}

void EnemySystem::Update(float time_elapsed) {
    for (auto& active_enemy : _active_enemies) {
        active_enemy->Update(time_elapsed);
    }
    /* здесь будет возрождение врагов */
}

void EnemySystem::Render(sf::RenderTarget &target) const {
    for (auto& active_enemy : _active_enemies) {
        active_enemy->Render(target);
    }
}

void EnemySystem::AddUniqueEnemy(std::shared_ptr<Enemy> enemy) {
    _unique_enemies.push_back(std::move(enemy));
}







