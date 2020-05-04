//
// Created by dmitry on 4/29/20.
//

#include "AttributeFormulas.h"
#include "AttributeConstants.h"

double stats_formula::MaxHPFunction(const stats_formula::BaseStats &stats) {
    return stat_const::kHpVigorCoeff * stats.at(ATTRIBUTE_ID::VIGOR)->GetCurrentValue();
}

double stats_formula::MaxManaFunction(const stats_formula::BaseStats &stats) {
    return stat_const::kManaIntelligenceCoeff * stats.at(ATTRIBUTE_ID::INTELLIGENCE)->GetCurrentValue() +
           stat_const::kManaFaithCoeff * stats.at(ATTRIBUTE_ID::FAITH)->GetCurrentValue();

}

double stats_formula::PhysArmorFunction(const stats_formula::BaseStats &stats) {
    return pow((stat_const::kPhysArmorVigorCoeff * stats.at(ATTRIBUTE_ID::VIGOR)->GetCurrentValue() +
                stat_const::kPhysArmorStrengthCoeff * stats.at(ATTRIBUTE_ID::STRENGTH)->GetCurrentValue() +
                stat_const::kPhysArmorDexterityCoeff * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue()) /
               stat_const::kPhysArmorNormalizeCoeff, stat_const::kPhysArmorMainPow);
}

double stats_formula::MagArmorFunction(const stats_formula::BaseStats &stats) {
    return pow((stat_const::kMagArmorFaithCoeff * stats.at(ATTRIBUTE_ID::FAITH)->GetCurrentValue() +
                stat_const::kMagArmorVigorCoeff * stats.at(ATTRIBUTE_ID::VIGOR)->GetCurrentValue() +
                stat_const::kMagArmorIntelligenceCoeff * stats.at(ATTRIBUTE_ID::INTELLIGENCE)->GetCurrentValue()) /
               stat_const::kMagArmorNormalizeCoeff, stat_const::kMagArmorMainPow);
}

double stats_formula::AttackSpeedFunction(const stats_formula::BaseStats &stats) {
    return stat_const::kAttackSpeedDexterityCoeff * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue() +
           stat_const::kAttackSpeedStrengthCoeff * stats.at(ATTRIBUTE_ID::STRENGTH)->GetCurrentValue() +
           stat_const::kAttackSpeedIntelligenceCoeff * stats.at(ATTRIBUTE_ID::INTELLIGENCE)->GetCurrentValue();
}

double stats_formula::BaseDamageFunction(const stats_formula::BaseStats &stats) {
    return (stat_const::kBaseDamageStrengthCoeff * stats.at(ATTRIBUTE_ID::STRENGTH)->GetCurrentValue() +
            stat_const::kBaseDamageDexterityCoeff * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue()) /
            stat_const::kBaseDamageNormalizeCoeff;
}

double stats_formula::CritChanceFunction(const stats_formula::BaseStats &stats) {
    return pow((stat_const::kCritChanceLuckCoeff * stats.at(ATTRIBUTE_ID::LUCK)->GetCurrentValue() +
                stat_const::kCritChanceDexterityCoeff * stats.at(ATTRIBUTE_ID::DEXTERITY)->GetCurrentValue()) /
                stat_const::kCritChanceNormalizeCoeff, stat_const::kCritChanceMainPow);
}
