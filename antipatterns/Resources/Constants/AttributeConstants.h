//
// Created by dmitry on 5/4/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTECONSTANTS_H
#define ANTIPATTERNS_ATTRIBUTECONSTANTS_H

namespace stat_const {
    const double kHpVigorCoeff = 10.0;

    const double kManaIntelligenceCoeff = 3.0;
    const double kManaFaithCoeff = 1.0;

    const double kPhysArmorVigorCoeff = 2.0;
    const double kPhysArmorStrengthCoeff = 1.0;
    const double kPhysArmorDexterityCoeff = 1.0;
    const double kPhysArmorNormalizeCoeff = 4.0;
    const double kPhysArmorMainPow = 0.7;

    const double kMagArmorFaithCoeff = 2.0;
    const double kMagArmorVigorCoeff = 1.0;
    const double kMagArmorIntelligenceCoeff = 1.0;
    const double kMagArmorNormalizeCoeff = 4.0;
    const double kMagArmorMainPow = 0.7;

    const double kAttackSpeedDexterityCoeff = 3.0;
    const double kAttackSpeedStrengthCoeff = 1.0;
    const double kAttackSpeedIntelligenceCoeff = 1.0;

    const double kBaseDamageStrengthCoeff = 5.0;
    const double kBaseDamageDexterityCoeff = 1.0;
    const double kBaseDamageNormalizeCoeff = 6.0;

    const double kCritChanceLuckCoeff = 5.0;
    const double kCritChanceDexterityCoeff = 1.0;
    const double kCritChanceNormalizeCoeff = 8.0;
    const double kCritChanceMainPow = 0.8;

} //namespace stats_constants

#endif //ANTIPATTERNS_ATTRIBUTECONSTANTS_H
