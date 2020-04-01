//
// Created by dmitry on 3/30/20.
//

#ifndef ANTIPATTERNS_PLAYER_H
#define ANTIPATTERNS_PLAYER_H


#include "Creature.h"
/* здесь я сижу сейчас */
class Player : public Creature {
public:
    Player(sf::Vector2f position, sf::Texture& texture_sheet);
    ~Player() override;
    /* overrided functions */
    void Update(float time_elapsed) override;
    void Render(sf::RenderTarget &target) override;
private:
    /* initializers */
    void InitAnimations();

    void UpdateAnimations(float time_elapsed);
    sf::Vector2f _position;
};


#endif //ANTIPATTERNS_PLAYER_H
