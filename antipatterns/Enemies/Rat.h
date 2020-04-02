//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_RAT_H
#define ANTIPATTERNS_RAT_H

#include "../src/Enemy.h"

class Rat : public Enemy {
public:
    Rat(const sf::Vector2f& position, sf::Texture& texture_sheet);
    ~Rat() = default;

    void Update(float time_elapsed) override;
    void Render(sf::RenderTarget& target) override;
    std::unique_ptr<Enemy> Clone(const sf::Vector2f& pos, int level) override;
private:
    void InitAnimations();

    void UpdateAnimations(float time_elapsed);
};


#endif //ANTIPATTERNS_RAT_H
