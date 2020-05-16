//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ENEMYSYSTEM_H
#define ANTIPATTERNS_ENEMYSYSTEM_H

#include "../Enemies/EnemySpawner.h"
#include "../Enemies/Rat.h"

struct EnemyParams {
  EnemyType _type{};
  int _level{1};
  EnemyType _type_to_spawn{EnemyType::DEFAULT};
};

class EnemySystem {
public:
  EnemySystem(const std::map<std::string, Json::Node> &enemies_settings,
              const std::unordered_map<EnemyType, std::shared_ptr<Enemy>>
                  &unique_enemies,
              const TileMap &tile_map);

  ~EnemySystem();

  void LoadEnemies(const std::map<std::string, Json::Node> &enemies_settings,
                   const std::unordered_map<EnemyType, std::shared_ptr<Enemy>>
                       &unique_enemies);

  auto begin() {
    return active_enemies_.begin();
  }

  auto end() {
    return active_enemies_.end();
  }

  void CreateEnemy(EnemyParams params, const sf::Vector2f &pos,
                   const std::unordered_map<EnemyType, std::shared_ptr<Enemy>>
                       &unique_enemies);

  void Update(float time_elapsed);

  void Render(sf::RenderTarget &target) const;

  void SetPlayer(std::shared_ptr<Creature> player);

private:
  void UpdatePlayer(float time_elapsed);
  void InitAStar(const std::vector<std::vector<int>> &cost_map, int grid_size);

  std::list<std::unique_ptr<Enemy>> active_enemies_;
  std::list<std::unique_ptr<Enemy>> dead_enemies_;
  std::shared_ptr<Creature> player_;
  std::shared_ptr<AStar> a_star_;

  static const std::unordered_map<std::string, EnemyType> names_to_types_;
};

#endif // ANTIPATTERNS_ENEMYSYSTEM_H
