//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_CREATURE_H
#define ANTIPATTERNS_CREATURE_H

#include "../Components/GraphicsComponent.h"


/* class that in fact implements basic sprite inteface */
class Creature {
public:
    Creature();

    virtual ~Creature();

    /* functions */
    virtual void Update(float time_elapsed) = 0;
    virtual void Render(const std::shared_ptr<sf::RenderTarget> &target) = 0;
    /* do not change signature */
    virtual void SetPosition(const sf::Vector2f &position);
    virtual void Move(float time_elapsed, const sf::Vector2f &direction);

    /* initializers */
    void SetTexture(std::shared_ptr<sf::Texture> texture);
    void InitPhysicsComponent(float max_velocity, float acceleration, float deceleration);
    void InitGraphicsComponent();

protected:
    std::unique_ptr<PhysicsComponent> _phys_comp{};
    std::unique_ptr<GraphicsComponent> _graph_comp{};
    /* for drawing */
    std::shared_ptr<sf::Texture> _texture{};
    sf::Sprite _sprite{};
private:

};


#endif //ANTIPATTERNS_CREATURE_H
