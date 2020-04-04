//
// Created by dmitry on 3/31/20.
//

#include "Enemy.h"

Enemy::Enemy() {

}

Enemy::Enemy(const Enemy &other) : Creature(other) {
    std::cout << "enemy copied" << std::endl;
}

Enemy::~Enemy() {

}

void Enemy::GenerateAttributes(int level) {

}


