//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_CREATURE_H
#define ANTIPATTERNS_CREATURE_H

#include "../Components/AttributeComponent.h"
#include "../Components/HitboxComponent.h"



/* class that in fact implements basic sprite inteface */
class Creature {
public:
    Creature();

    Creature(const Creature &other);

    virtual ~Creature();

    /* pure functions */
    virtual void Update(float time_elapsed) = 0;
    virtual void Render(sf::RenderTarget &target) = 0;
    /* do not change signature */
    virtual void SetPosition(const sf::Vector2f &position);
    virtual void Move(float time_elapsed, const sf::Vector2f &direction);

    /* initializers */
    void SetTexture(sf::Texture& texture);
    void InitPhysicsComponent(float max_velocity, float acceleration, float deceleration);
    void InitGraphicsComponent(sf::Texture& texture_sheet);
    void InitHitboxComponent(sf::Sprite& sprite, float width, float height, float offset_x, float offset_y);
    void InitAttributeComponent(int level);

protected:
    std::unique_ptr<PhysicsComponent> _phys_comp{};
    std::unique_ptr<GraphicsComponent> _graph_comp{};
    std::unique_ptr<HitboxComponent> _hitbox_comp{};
    std::unique_ptr<AttributeComponent> _attribute_comp{};
    /* for drawing */
    sf::Sprite _sprite{};
private:

};


#endif //ANTIPATTERNS_CREATURE_H
