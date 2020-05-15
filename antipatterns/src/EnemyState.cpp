//
// Created by dmitry on 5/4/20.
//

#include "EnemyState.h"
#include "Enemy.h"

EnemyStateType EnemyState::GetStateType() const { return type_; }

IdleState::IdleState(sf::Vector2f base_point, float aggro_radius)
    : EnemyState(EnemyStateType::IDLE), base_point(base_point),
      aggro_radius_(aggro_radius) {}

EnemyStateType IdleState::Update(float time_elapsed, Enemy &enemy,
                                 std::shared_ptr<Creature> &player) {
  if (enemy.GetDistance(*player) >= aggro_radius_) {
    return EnemyStateType::IDLE;
  } else {
    sf::Vector2f enemy_pos = enemy.GetCenteredPosition();
    sf::Vector2f pl_pos = player->GetCenteredPosition();
    if (enemy.GetPursuingStrategy()->IsLineSolid(enemy_pos.x, enemy_pos.y,
                                                 pl_pos.x, pl_pos.y)) {
      return EnemyStateType::IDLE;
    }
    return EnemyStateType::PURSUING;
  }
}

EnemyStateType PursuingState::Update(float time_elapsed, Enemy &enemy,
                                     std::shared_ptr<Creature> &player) {

}
