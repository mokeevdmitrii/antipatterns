//
// Created by dmitry on 5/3/20.
//

#include "InputHandler.h"
PlayerInputHandler::PlayerInputHandler(
    std::shared_ptr<Creature> player,
    std::shared_ptr<std::unordered_map<std::string, int>> keybindings)
    : player_(std::move(player)), keybindings_(std::move(keybindings)) {}

void PlayerInputHandler::UpdateInput(float time_elapsed) {
  if (sf::Keyboard::isKeyPressed(
          static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_LEFT")))) {
    if (last_command_ != nullptr)
      last_command_->Undo();
    last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_LEFT"));
    last_command_ = std::make_shared<MoveCommand>(player_, time_elapsed,
                                                  sf::Vector2f(-1.f, 0.f));
  } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                 keybindings_->at("MOVE_RIGHT")))) {
    if (last_command_ != nullptr)
      last_command_->Undo();
    last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_RIGHT"));
    last_command_ = std::make_shared<MoveCommand>(player_, time_elapsed,
                                                  sf::Vector2f(1.f, 0.f));
  } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                 keybindings_->at("MOVE_DOWN")))) {
    if (last_command_ != nullptr)
      last_command_->Undo();
    last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_DOWN"));
    last_command_ = std::make_shared<MoveCommand>(player_, time_elapsed,
                                                  sf::Vector2f(0.f, 1.f));
  } else if (sf::Keyboard::isKeyPressed(
                 static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_UP")))) {
    if (last_command_ != nullptr)
      last_command_->Undo();
    last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_UP"));
    last_command_ = std::make_shared<MoveCommand>(player_, time_elapsed,
                                                  sf::Vector2f(0.f, -1.f));
  } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                 keybindings_->at("TELEPORT")))) {
    if (last_key_ !=
        static_cast<sf::Keyboard::Key>(keybindings_->at("TELEPORT"))) {
      if (last_command_ != nullptr)
        last_command_->Undo();
      last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("TELEPORT"));
      last_command_ = std::make_shared<TeleportCommand>(player_);
    }
  } else if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(
                 keybindings_->at("HARAKIRI")))) {
    if (last_key_ !=
        static_cast<sf::Keyboard::Key>(keybindings_->at("HARAKIRI"))) {
      if (last_command_ != nullptr) {
        last_command_->Undo();
      }
      last_key_ = static_cast<sf::Keyboard::Key>(keybindings_->at("HARAKIRI"));
      last_command_ = std::make_shared<BaseSkillCommand>(
          player_, command_const::kHarakiriKey);
    }
  } else {
    if (last_command_ != nullptr) {
      last_command_->Undo();
      Reset();
    }
  }
  Update(time_elapsed);
}

std::shared_ptr<GameCommand> PlayerInputHandler::GetLastCommand() {
  return last_command_;
}
void PlayerInputHandler::Reset() {
  last_key_ = kUnknownKey;
  last_command_ = nullptr;
}
void PlayerInputHandler::Update(float time_elapsed) {
  TeleportCommand::Update(time_elapsed);
}
