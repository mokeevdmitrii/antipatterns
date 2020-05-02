//
// Created by dmitry on 3/28/20.
//

#ifndef ANTIPATTERNS_CREATURE_H
#define ANTIPATTERNS_CREATURE_H

#include "../Components/AttributeComponent.h"
#include "../Components/HitboxComponent.h"
#include "Tile.h"


class Creature {
public:
    Creature();
    Creature& operator = (const Creature& other);
    Creature(const Creature &other);

    virtual ~Creature();

    /* pure functions */
    virtual void Update(float time_elapsed) = 0;
    virtual void Render(sf::RenderTarget &target) const = 0;
    /* do not change signature */
    virtual void SetPosition(const sf::Vector2f &position);
    virtual void Move(float time_elapsed, const sf::Vector2f &direction);
    //для актуализации параметров в случае чево)
    //virtual void Actualize() = 0;

    /* initializers */
    void SetTexture(sf::Texture& texture);
    void InitPhysicsComponent(const std::map<std::string, Json::Node> &settings);
    void InitGraphicsComponent(const sf::Texture &texture_sheet, const std::map<std::string, Json::Node> &settings);
    void InitHitboxComponent(const std::map<std::string, Json::Node> &settings);
    void InitAttributeComponent(const std::map<std::string, Json::Node> &settings);

    /* getters */
    sf::Vector2f GetPosition() const;
    void SetPossibleMoveDirections(PossibleDirections directions);
    sf::RectangleShape GetHitbox() const;

    bool Intersects(const sf::RectangleShape &other_hitbox) const;
    bool Contains(const sf::RectangleShape &other_hitbox) const;
    bool ContainedIn(const sf::RectangleShape &other_hitbox) const;

protected:
    std::unique_ptr<PhysicsComponent> phys_comp_{};
    std::unique_ptr<GraphicsComponent> graph_comp_{};
    std::unique_ptr<HitboxComponent> hitbox_comp_{};
    std::unique_ptr<AttributeComponent> attribute_comp_{};
    /* for drawing */
    sf::Sprite sprite_{};
private:

};


#endif //ANTIPATTERNS_CREATURE_H
