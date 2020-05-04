//
// Created by dmitry on 4/29/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTEFORMULAS_H
#define ANTIPATTERNS_ATTRIBUTEFORMULAS_H

#include "../../Components/Parameters/BaseAttribute.h"

namespace stats_formula {
    using BaseStats = std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>>;
    using StatsFunc = std::function<double(const std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>> &)>;

    double MaxHPFunction(const BaseStats &stats);

    double MaxManaFunction(const BaseStats &stats);

    double PhysArmorFunction(const BaseStats &stats);

    double MagArmorFunction(const BaseStats &stats);

    double AttackSpeedFunction(const BaseStats &stats);

    double BaseDamageFunction(const BaseStats &stats);

    double CritChanceFunction(const BaseStats &stats);
}

#endif //ANTIPATTERNS_ATTRIBUTEFORMULAS_H
