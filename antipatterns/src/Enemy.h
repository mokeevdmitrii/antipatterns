//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_ENEMY_H
#define ANTIPATTERNS_ENEMY_H


#include "Creature.h"

class Enemy : public Creature {
public:
    Enemy();
    Enemy(const Enemy& other);
    ~Enemy();

    void GenerateAttributes(int level);
    virtual std::unique_ptr<Enemy> Clone() = 0;
private:

};


#endif //ANTIPATTERNS_ENEMY_H
