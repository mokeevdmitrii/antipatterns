//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTECOMPONENT_H
#define ANTIPATTERNS_ATTRIBUTECOMPONENT_H

#include "GraphicsComponent.h"

class AttributeComponent {
public:
    AttributeComponent(int level);
    ~AttributeComponent() = default;

    int GetLevel();
private:
    int _level;
};


#endif //ANTIPATTERNS_ATTRIBUTECOMPONENT_H
