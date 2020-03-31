//
// Created by dmitry on 3/30/20.
//

#ifndef ANTIPATTERNS_PLAYER_H
#define ANTIPATTERNS_PLAYER_H


#include "Creature.h"
/* здесь я сижу сейчас */
class Player : public Creature {
public:
    Player(sf::Vector2f position, std::shared_ptr<sf::Texture> texture);
    ~Player() override;
    /* overrided functions */
    void Update(float time_elapsed) override;
    void Render(const std::shared_ptr<sf::RenderTarget> &target) override;

    /* initializers */
    void InitComponents();
private:
    sf::Vector2f _position;
    std::shared_ptr<sf::Texture> _texture;
};


#endif //ANTIPATTERNS_PLAYER_H
