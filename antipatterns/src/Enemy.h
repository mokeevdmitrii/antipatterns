//
// Created by dmitry on 3/31/20.
//

#ifndef ANTIPATTERNS_ENEMY_H
#define ANTIPATTERNS_ENEMY_H


#include "Creature.h"

class Enemy : public Creature {
public:
    Enemy();
    ~Enemy();

    std::shared_ptr<Enemy> Clone(int level) const;

private:

};


#endif //ANTIPATTERNS_ENEMY_H
