//
// Created by dmitry on 5/3/20.
//

#ifndef ANTIPATTERNS_INPUTHANDLER_H
#define ANTIPATTERNS_INPUTHANDLER_H

#include "Command.h"

class PlayerInputHandler {
public:
  PlayerInputHandler(
      std::shared_ptr<Creature> player,
      std::shared_ptr<std::unordered_map<std::string, int>> keybindings)
      : player_(std::move(player)), keybindings_(std::move(keybindings)) {}

  void UpdateInput(float time_elapsed) {
    if (sf::Keyboard::isKeyPressed(
            static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_LEFT")))) {
      if (last_command_ != nullptr)
        last_command_->Undo();
      last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_LEFT"));
      last_command_ = std::make_unique<MoveCommand>(player_, time_elapsed,
                                                    sf::Vector2f(-1.f, 0.f));
    } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                   keybindings_->at("MOVE_RIGHT")))) {
      if (last_command_ != nullptr)
        last_command_->Undo();
      last_key_ =
          static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_RIGHT"));
      last_command_ = std::make_unique<MoveCommand>(player_, time_elapsed,
                                                    sf::Vector2f(1.f, 0.f));
    } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                   keybindings_->at("MOVE_DOWN")))) {
      if (last_command_ != nullptr)
        last_command_->Undo();
      last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_DOWN"));
      last_command_ = std::make_unique<MoveCommand>(player_, time_elapsed,
                                                    sf::Vector2f(0.f, 1.f));
    } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                   keybindings_->at("MOVE_UP")))) {
      if (last_command_ != nullptr)
        last_command_->Undo();
      last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_UP"));
      last_command_ = std::make_unique<MoveCommand>(player_, time_elapsed,
                                                    sf::Vector2f(0.f, -1.f));
    } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                   keybindings_->at("TELEPORT")))) {
      if (last_key_ != static_cast<sf::Keyboard::Key>(
                           keybindings_->at("TELEPORT"))) {
        if (last_command_ != nullptr) last_command_->Undo();
        last_key_ = static_cast<sf::Keyboard::Key>(
            keybindings_->at("TELEPORT"));
        last_command_ = std::make_unique<TeleportCommand>(player_);
      }
    } else {
      if (last_command_ != nullptr) {
        last_command_->Undo();
        last_key_ = kUnknownKey;
      }
    }
      if (last_command_ != nullptr) {
        last_command_->Execute(time_elapsed);
        if (last_command_->IsDone()) {
          last_command_ = nullptr;
          last_key_ = kUnknownKey;
        }
      }
  }

private:
  sf::Keyboard::Key last_key_;
  std::shared_ptr<std::unordered_map<std::string, int>> keybindings_;
  std::shared_ptr<Creature> player_;
  std::unique_ptr<GameCommand> last_command_;
};

#endif // ANTIPATTERNS_INPUTHANDLER_H
