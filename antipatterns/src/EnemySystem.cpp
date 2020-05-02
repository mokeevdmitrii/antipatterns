//
// Created by dmitry on 4/2/20.
//

#include "EnemySystem.h"

const std::unordered_map<std::string, EnemyType> EnemySystem::names_to_types_ = {
        {"enemy_spawner", EnemyType::ENEMY_SPAWNER},
        {"rat",           EnemyType::RAT}
};


/* constructors and destructors */


EnemySystem::EnemySystem(const std::map<std::string, Json::Node> &enemies_settings,
                         const std::unordered_map<EnemyType, std::shared_ptr<Enemy>> &unique_enemies) {
    LoadEnemies(enemies_settings, unique_enemies);
}

EnemySystem::~EnemySystem() {

}


void EnemySystem::LoadEnemies(const std::map<std::string, Json::Node> &enemies_settings,
                              const std::unordered_map<EnemyType, std::shared_ptr<Enemy>> &unique_enemies) {
    std::vector<Json::Node> tile_size_array = enemies_settings.at("tile_size").AsArray();
    sf::Vector2i tile_size = sf::Vector2i(tile_size_array.at(0).AsDouble(), tile_size_array.at(1).AsDouble());
    const std::vector<Json::Node> enemies = enemies_settings.at("enemies").AsArray();
    for (const auto &node : enemies) {
        const auto &enemy_settings = node.AsMap();
        EnemyType enemy_type = names_to_types_.at(enemy_settings.at("type").AsString());
        int enemy_level = static_cast<int>(enemy_settings.at("level").AsDouble());
        EnemyType type_to_spawn{};
        if (enemy_settings.count("type_to_spawn") != 0) {
            type_to_spawn = static_cast<EnemyType>(enemy_settings.at("type_to_spawn").AsDouble());
        }
        auto json_pos = enemy_settings.at("pos").AsArray();
        auto rel_pos = sf::Vector2f(json_pos.at(0).AsDouble(), json_pos.at(1).AsDouble());
        CreateEnemy({enemy_type, enemy_level, type_to_spawn},
                    sf::Vector2f(rel_pos.x * tile_size.x, rel_pos.y * tile_size.y), unique_enemies);
    }
}


void EnemySystem::CreateEnemy(EnemyParams params, const sf::Vector2f &pos,
                              const std::unordered_map<EnemyType, std::shared_ptr<Enemy>> &unique_enemies) {
    std::unique_ptr<Enemy> clone = unique_enemies.at(params._type)->Clone();
    clone->GenerateAttributes(params._level);
    /* if is a correct-defined spawner */
    if (params._type_to_spawn != EnemyType::DEFAULT) {
        auto &_spawner = dynamic_cast<EnemySpawner &>(*clone);
        _spawner.SetPrototype(unique_enemies.at(params._type_to_spawn));
    }
    clone->SetPosition(pos);
    active_enemies_.push_back(std::move(clone));
}

void EnemySystem::Update(float time_elapsed) {
    if (player_ != nullptr) {
        UpdatePlayer(time_elapsed);
    }
    for (auto &active_enemy : active_enemies_) {
        active_enemy->Update(time_elapsed);
    }
    /* здесь будет возрождение врагов */
}

void EnemySystem::Render(sf::RenderTarget &target) const {
    for (auto &active_enemy : active_enemies_) {
        active_enemy->Render(target);
    }
}

void EnemySystem::SetPlayer(std::shared_ptr<Creature> player) {
    player_ = std::move(player);
}


void EnemySystem::UpdatePlayer(float time_elapsed) {
    for (auto &enemy_alive : active_enemies_) {
        enemy_alive->UpdatePlayer(time_elapsed, player_);
    }
}








