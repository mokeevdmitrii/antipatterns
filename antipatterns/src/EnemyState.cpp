//
// Created by dmitry on 5/4/20.
//

#include "EnemyState.h"

EnemyStateType EnemyState::GetStateType() const { return type_; }

IdleState::IdleState(sf::Vector2f base_point, float aggro_radius)
    : EnemyState(EnemyStateType::IDLE), base_point(base_point),
      aggro_radius_(aggro_radius) {}

EnemyStateType IdleState::Update(float time_elapsed, Creature &enemy,
                                 std::shared_ptr<Creature> &player,
                                 const std::unique_ptr<TileMap> &tile_map) {
  return EnemyStateType::IDLE;
}

EnemyStateType PursuingState::Update(float time_elapsed, Creature &enemy,
                                     std::shared_ptr<Creature> &player,
                                     const std::unique_ptr<TileMap> &tile_map) {

}
