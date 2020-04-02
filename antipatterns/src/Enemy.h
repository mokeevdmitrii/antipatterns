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

    //virtual void Update(float time_elapsed) = 0;
    //virtual void Render(sf::RenderTarget target) = 0;

    virtual std::unique_ptr<Enemy> Clone(const sf::Vector2f& pos, int level) = 0;
private:

};


#endif //ANTIPATTERNS_ENEMY_H
