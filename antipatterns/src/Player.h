//
// Created by dmitry on 3/30/20.
//

#ifndef ANTIPATTERNS_PLAYER_H
#define ANTIPATTERNS_PLAYER_H


#include "Creature.h"

class PlayerInputComponent;

/* здесь я сижу сейчас */
class Player : public Creature {
public:
    Player(sf::Vector2f position, sf::Texture &texture_sheet, const std::string &file_name,
           std::shared_ptr<std::unordered_map<std::string, int>> keybindings);
    ~Player() override;
    /* special input functions */

    /* overrided functions */
    void Update(float time_elapsed) override;
    void Render(sf::RenderTarget &target) const override;
private:
    void UpdateInput(float time_elapsed);
    void UpdateAnimations(float time_elapsed);

    std::shared_ptr<std::unordered_map<std::string, int>> keybindings_;
    sf::Vector2f position_;
    // std::shared_ptr<Equipment> equipment;

};


#endif //ANTIPATTERNS_PLAYER_H
