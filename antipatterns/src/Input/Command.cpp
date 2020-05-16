//
// Created by dmitry on 5/3/20.
//

#include "Command.h"
bool GameCommand::IsDone() { return is_done; }
MoveCommand::MoveCommand(std::shared_ptr<Creature> actor, float time_elapsed,
                         sf::Vector2f direction)
    : GameCommand(std::move(actor)), direction_(direction),
      time_elapsed_(time_elapsed) {}

void MoveCommand::Execute(float time_elapsed) {
  actor_->Move(time_elapsed, direction_);
  is_done = true;
}
void MoveCommand::Undo() {}

TeleportCommand::TeleportCommand(std::shared_ptr<Creature> actor)
    : GameCommand(std::move(actor)) {}

void TeleportCommand::Execute(float time_elapsed) {
  time_elapsed_ += time_elapsed;
  if (time_elapsed_ >= command_const::kTeleportTime) {
    MovementState last = actor_->GetPhysicsComponent()->GetLastMoveDirection();
    sf::Vector2f pos = actor_->GetPosition();
    if (last == MovementState::MOVING_LEFT) {
      actor_->SetPosition({pos.x - command_const::kTeleportDistance, pos.y});
    } else if (last == MovementState::MOVING_RIGHT) {
      actor_->SetPosition({pos.x + command_const::kTeleportDistance, pos.y});
    } else if (last == MovementState::MOVING_UP) {
      actor_->SetPosition({pos.x, pos.y - command_const::kTeleportDistance});
    } else if (last == MovementState::MOVING_DOWN) {
      actor_->SetPosition({pos.x, pos.y + command_const::kTeleportDistance});
    }
    is_done = true;
  }
}

void TeleportCommand::Undo() {
  time_elapsed_ = 0;
}
