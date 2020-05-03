//
// Created by dmitry on 5/3/20.
//

#ifndef ANTIPATTERNS_COMMAND_H
#define ANTIPATTERNS_COMMAND_H

#include "../Player.h"

class GameCommand  {
public:
    explicit GameCommand(std::shared_ptr<Creature> actor) : actor_(std::move(actor)) {}

    virtual void Execute(float time_elapsed) = 0;

    virtual void Undo() = 0;

    bool IsDone() {
        return is_done;
    }

protected:
    std::shared_ptr<Creature> actor_;
    bool is_done{false};
};

class MoveCommand : public GameCommand {
public:
    MoveCommand(std::shared_ptr<Creature> actor, float time_elapsed, sf::Vector2f direction) : GameCommand(
            std::move(actor)), direction_(direction), time_elapsed_(time_elapsed) {

    }

    void Execute(float time_elapsed) override {
        actor_->Move(time_elapsed, direction_);
        is_done = true;
    }

    void Undo() override {};

private:
    float time_elapsed_;
    sf::Vector2f direction_;
};

class BaseSkillCommand : public GameCommand {
    BaseSkillCommand(std::shared_ptr<Creature> actor) : GameCommand(std::move(actor)) {

    }
};

class TeleportCommand {

};


#endif //ANTIPATTERNS_COMMAND_H
