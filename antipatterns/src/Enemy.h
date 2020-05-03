//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_ENEMY_H
#define ANTIPATTERNS_ENEMY_H


#include "Creature.h"
#include "EnemyTypes.h"
#include "EnemyState.h"


class Enemy : public Creature {
public:
    Enemy();
    Enemy(const Enemy& other);
    ~Enemy() override;

    //should be implemented as soon as possible
    //if (current_state_id_ != states_.at(current_state_id).Update(...) -> ChangeState(...)))
    virtual void Update(float time_elapsed, const std::unique_ptr<TileMap> &tile_map, std::shared_ptr<Creature> &player) = 0;

    virtual void UpdatePlayer(float time_elapsed, const std::shared_ptr<Creature>& player);
    void GenerateAttributes(int level);
    virtual std::unique_ptr<Enemy> Clone() const = 0;
private:
    std::unordered_map<EnemyStateType, std::unique_ptr<EnemyState>> states_;
    EnemyStateType current_state_id_{EnemyStateType::IDLE};
};


#endif //ANTIPATTERNS_ENEMY_H
