//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTECOMPONENT_H
#define ANTIPATTERNS_ATTRIBUTECOMPONENT_H

#include "GraphicsComponent.h"
#include "Parameters/Attribute.h"

class AttributeComponent {
public:
    explicit AttributeComponent(const std::map<std::string, Json::Node>& settings);
    AttributeComponent(const AttributeComponent& other);
    AttributeComponent& operator = (const AttributeComponent& other);
    ~AttributeComponent() = default;

    void LoadFromMap(const std::map<std::string, Json::Node>& settings);

    int GetLevel() const;
private:
    int _level{1};
    int _health;
    int _health_per_level;
};


#endif //ANTIPATTERNS_ATTRIBUTECOMPONENT_H
