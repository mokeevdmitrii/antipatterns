//
// Created by dmitry on 4/29/20.
//

#include "AttributeFormulas.h"

double ATTRIBUTE_FORMULAS::MaxHPFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return 10.0 * stats.at(ATTRIBUTE_ID::VIGOR)->GetCurrentValue();
}

double ATTRIBUTE_FORMULAS::MaxManaFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return 3.0 * stats.at(ATTRIBUTE_ID::INTELLIGENCE)->GetCurrentValue() +
           1.0 * stats.at(ATTRIBUTE_ID::FAITH)->GetCurrentValue();

}

double ATTRIBUTE_FORMULAS::PhysArmorFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return pow((2.0 * stats.at(ATTRIBUTE_ID::VIGOR)->GetCurrentValue() +
                1.0 * stats.at(ATTRIBUTE_ID::STRENGTH)->GetCurrentValue() +
                1.0 * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue()) / 4.0, 0.7);
}

double ATTRIBUTE_FORMULAS::MagArmorFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return pow((2.0 * stats.at(ATTRIBUTE_ID::FAITH)->GetCurrentValue() +
                1.0 * stats.at(ATTRIBUTE_ID::VIGOR)->GetCurrentValue() +
                1.0 * stats.at(ATTRIBUTE_ID::INTELLIGENCE)->GetCurrentValue()) / 4.0, 0.7);
}

double ATTRIBUTE_FORMULAS::AttackSpeedFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return 3.0 * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue() +
           1.0 * stats.at(ATTRIBUTE_ID::STRENGTH)->GetCurrentValue() +
           1.0 * stats.at(ATTRIBUTE_ID::INTELLIGENCE)->GetCurrentValue();
}

double ATTRIBUTE_FORMULAS::BaseDamageFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return (5.0 * stats.at(ATTRIBUTE_ID::STRENGTH)->GetCurrentValue() +
            1.0 * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue()) / 6.0;
}

double ATTRIBUTE_FORMULAS::CritChanceFunction(const ATTRIBUTE_FORMULAS::BaseStats &stats) {
    return pow((5.0 * stats.at(ATTRIBUTE_ID::LUCK)->GetCurrentValue() +
                1.0 * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue()) / 8.0, 0.8);
}
