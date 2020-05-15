//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_ENEMY_H
#define ANTIPATTERNS_ENEMY_H

#include "../Enemies/EnemyTypes.h"
#include "Creature.h"
#include "EnemyState.h"

class Enemy : public Creature {
public:
  Enemy();
  Enemy(const Enemy &other);
  ~Enemy() override;

  void SetPursuingStrategy(std::shared_ptr<AStar> a_star);
  std::shared_ptr<AStar> GetPursuingStrategy() const;

  virtual void UpdateEnemy(float time_elapsed,
                           const std::unique_ptr<TileMap> &tile_map,
                           std::shared_ptr<Creature> &player);

  virtual void UpdatePlayer(float time_elapsed,
                            const std::shared_ptr<Creature> &player);
  void GenerateAttributes(int level);
  virtual std::unique_ptr<Enemy> Clone() const = 0;

protected:
  void InitStates();

  std::shared_ptr<AStar> a_star_;
  std::unordered_map<EnemyStateType, std::unique_ptr<EnemyState>> states_;
  EnemyStateType current_state_id_{EnemyStateType::IDLE};
};

#endif // ANTIPATTERNS_ENEMY_H
