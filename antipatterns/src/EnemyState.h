//
// Created by dmitry on 5/4/20.
//

#ifndef ANTIPATTERNS_ENEMYSTATE_H
#define ANTIPATTERNS_ENEMYSTATE_H

#include "../Resources/AStar.h"
#include "Creature.h"
#include "TileMap.h"

class Enemy;

enum class EnemyStateType { IDLE = 0, PURSUING = 1, FIGHTING = 2 };

class EnemyState {
public:
  explicit EnemyState(EnemyStateType type) : type_(type) {}

  virtual EnemyStateType Update(float time_elapsed, Enemy &enemy,
                                std::shared_ptr<Creature> &player) = 0;

  EnemyStateType GetStateType() const;

private:
  EnemyStateType type_{};
};

class PursuingState : public EnemyState {
public:
  PursuingState(std::shared_ptr<AStar> a_star);

  EnemyStateType Update(float time_elapsed, Enemy &enemy,
                        std::shared_ptr<Creature> &player) override;

private:
  std::shared_ptr<AStar> a_star_;
};

class FightingState : public EnemyState {
public:
  FightingState() = default;

  EnemyStateType Update(float time_elapsed, Enemy &enemy,
                        std::shared_ptr<Creature> &player) override;

private:
};

class IdleState : public EnemyState {
public:
  IdleState(sf::Vector2f base_point, float aggro_radius);

  EnemyStateType Update(float time_elapsed, Enemy &enemy,
                        std::shared_ptr<Creature> &player) override;

private:
  sf::Vector2f base_point;
  float aggro_radius_;
};

#endif // ANTIPATTERNS_ENEMYSTATE_H
