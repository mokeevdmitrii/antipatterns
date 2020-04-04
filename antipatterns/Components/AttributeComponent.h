//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTECOMPONENT_H
#define ANTIPATTERNS_ATTRIBUTECOMPONENT_H

#include "GraphicsComponent.h"

class AttributeComponent {
public:
    AttributeComponent(const std::map<std::string, Json::Node>& settings);
    ~AttributeComponent() = default;

    void LoadFromMap(const std::map<std::string, Json::Node>& settings);

    int GetLevel();
private:
    int _level{1};
    int _health;
    int _health_per_level;
};


#endif //ANTIPATTERNS_ATTRIBUTECOMPONENT_H
