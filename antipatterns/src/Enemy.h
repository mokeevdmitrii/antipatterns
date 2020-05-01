//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_ENEMY_H
#define ANTIPATTERNS_ENEMY_H


#include "Creature.h"
#include "EnemyTypes.h"


class Enemy : public Creature {
public:
    Enemy();
    Enemy(const Enemy& other);
    ~Enemy() override;

    virtual void UpdatePlayer(float time_elapsed, const std::shared_ptr<Creature>& player);
    void GenerateAttributes(int level);
    virtual std::unique_ptr<Enemy> Clone() const = 0;
private:

};


#endif //ANTIPATTERNS_ENEMY_H
