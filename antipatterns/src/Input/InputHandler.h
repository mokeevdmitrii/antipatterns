//
// Created by dmitry on 5/3/20.
//

#ifndef ANTIPATTERNS_INPUTHANDLER_H
#define ANTIPATTERNS_INPUTHANDLER_H

#include "Command.h"


class PlayerInputHandler {
public:
    PlayerInputHandler(std::shared_ptr<Creature> player,
                       std::shared_ptr<std::unordered_map<std::string, int>> keybindings) : player_(std::move(player)),
                                                                                            keybindings_(std::move(
                                                                                                    keybindings)) {}

    std::unique_ptr<GameCommand> UpdateInput(float time_elapsed) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_LEFT")))) {
            return std::make_unique<MoveCommand>(player_, time_elapsed, sf::Vector2f(-1.f, 0.f));
        }
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_DOWN")))) {
            return std::make_unique<MoveCommand>(player_, time_elapsed, sf::Vector2f(0.f, 1.f));
        }
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_RIGHT")))) {
            return std::make_unique<MoveCommand>(player_, time_elapsed, sf::Vector2f(1.f, 0.f));
        }
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keybindings_->at("MOVE_UP")))) {
            return std::make_unique<MoveCommand>(player_, time_elapsed, sf::Vector2f(0.f, -1.f));
        }
        return nullptr;
    }

private:
    std::shared_ptr<std::unordered_map<std::string, int>> keybindings_;
    std::shared_ptr<Creature> player_;
};


#endif //ANTIPATTERNS_INPUTHANDLER_H
