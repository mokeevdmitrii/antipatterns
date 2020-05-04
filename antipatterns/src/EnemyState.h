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
    virtual EnemyStateType
    Update(float time_elapsed, Creature* enemy, const std::unique_ptr<TileMap> &tile_map, std::shared_ptr<Creature> &player) = 0;

    EnemyStateType GetStateType() const;
private:
    EnemyStateType type_{};
};

class PursuingState : public EnemyState {
public:

private:

};

class FightingState : public EnemyState {
public:

private:
};

class IdleState : public EnemyState {
public:

private:
    sf::Vector2f base_point;
};

#endif //ANTIPATTERNS_ENEMYSTATE_H
