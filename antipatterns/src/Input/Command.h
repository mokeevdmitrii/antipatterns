//
// Created by dmitry on 5/3/20.
//

#ifndef ANTIPATTERNS_COMMAND_H
#define ANTIPATTERNS_COMMAND_H

#include "../Player.h"

class GameCommand {
public:
  explicit GameCommand(std::shared_ptr<Creature> actor)
      : actor_(std::move(actor)) {}

  virtual void Execute(float time_elapsed) = 0;

  virtual void Undo() = 0;

  bool IsDone();

protected:
  std::shared_ptr<Creature> actor_;
  bool is_done{false};
};

class MoveCommand : public GameCommand {
public:
  MoveCommand(std::shared_ptr<Creature> actor, float time_elapsed,
              sf::Vector2f direction);

  void Execute(float time_elapsed) override;

  void Undo() override;


private:
  float time_elapsed_;
  sf::Vector2f direction_;
};

class BaseSkillCommand : public GameCommand {
  BaseSkillCommand(std::shared_ptr<Creature> actor)
      : GameCommand(std::move(actor)) {}
};

class TeleportCommand : public GameCommand {
public:
  explicit TeleportCommand(std::shared_ptr<Creature> actor);

  void Execute(float time_elapsed) override;

  void Undo() override;
private:
  float time_elapsed_{0};
};

#endif // ANTIPATTERNS_COMMAND_H
