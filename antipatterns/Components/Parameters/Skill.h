//
// Created by dmitry on 4/25/20.
//

#ifndef ANTIPATTERNS_SKILL_H
#define ANTIPATTERNS_SKILL_H

#include "Effect.h"
#include "Attribute.h"
#include "../AttributeComponent.h"

enum class SkillType {
    TARGET,
    AOE
};

class Skill {
public:
    Skill(std::shared_ptr<Effect> effects);

    void Execute(AttributeComponent* one_component, AttributeComponent* other_component);
private:
    std::shared_ptr<std::vector<Effect>> effects_;
};


#endif //ANTIPATTERNS_SKILL_H
