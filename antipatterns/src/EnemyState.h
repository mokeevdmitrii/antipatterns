//
// Created by dmitry on 5/4/20.
//

#ifndef ANTIPATTERNS_ENEMYSTATE_H
#define ANTIPATTERNS_ENEMYSTATE_H

#include "Creature.h"
#include "TileMap.h"

enum class EnemyStateType {
    IDLE = 0,
    PURSUING = 1,
    FIGHTING = 2
};

class EnemyState {
public:
    EnemyState(EnemyStateType type) : type_(type) {}

    virtual EnemyStateType
    Update(float time_elapsed, Creature &enemy, std::shared_ptr<Creature> &player,
           const std::unique_ptr<TileMap> &tile_map) = 0;

    EnemyStateType GetStateType() const;

private:
    EnemyStateType type_{};
};

class PursuingState : public EnemyState {
public:
    PursuingState();

    EnemyStateType Update(float time_elapsed, Creature &enemy, std::shared_ptr<Creature> &player,
                          const std::unique_ptr<TileMap> &tile_map) override;

private:

};

class FightingState : public EnemyState {
public:
    FightingState() = default;

    EnemyStateType Update(float time_elapsed, Creature &enemy, std::shared_ptr<Creature> &player,
                          const std::unique_ptr<TileMap> &tile_map) override;
private:
};

class IdleState : public EnemyState {
public:
    IdleState(sf::Vector2f base_point, float aggro_radius);

    EnemyStateType Update(float time_elapsed, Creature &enemy, std::shared_ptr<Creature> &player,
                          const std::unique_ptr<TileMap> &tile_map) override;
private:
    sf::Vector2f base_point;
    float aggro_radius_;
};

#endif //ANTIPATTERNS_ENEMYSTATE_H
