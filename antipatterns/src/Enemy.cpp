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

//здесь в будущем будет карта и А* - возможно!
void Enemy::UpdatePlayer(float time_elapsed, const std::shared_ptr<Creature> &player) {
    sf::Vector2f player_pos = player->GetPosition();
    sf::Vector2f my_pos = GetPosition();
    Move(time_elapsed, {player_pos.x - my_pos.x, player_pos.y - my_pos.y});
}


