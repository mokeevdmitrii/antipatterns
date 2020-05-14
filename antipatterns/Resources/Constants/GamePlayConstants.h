//
// Created by dmitry on 5/4/20.
//

#ifndef ANTIPATTERNS_GAMEPLAYCONSTANTS_H
#define ANTIPATTERNS_GAMEPLAYCONSTANTS_H

#include <vector>

namespace room_const {
constexpr float kInitPlayerX = 100;
constexpr float kInitPlayerY = 400;

constexpr int kSolidTileValue = -1;
} // namespace room_const

namespace stat_const {
constexpr double kHpVigorCoeff = 10.0;

constexpr double kManaIntelligenceCoeff = 3.0;
constexpr double kManaFaithCoeff = 1.0;

constexpr double kPhysArmorVigorCoeff = 2.0;
constexpr double kPhysArmorStrengthCoeff = 1.0;
constexpr double kPhysArmorDexterityCoeff = 1.0;
constexpr double kPhysArmorNormalizeCoeff = 4.0;
constexpr double kPhysArmorMainPow = 0.7;

constexpr double kMagArmorFaithCoeff = 2.0;
constexpr double kMagArmorVigorCoeff = 1.0;
constexpr double kMagArmorIntelligenceCoeff = 1.0;
constexpr double kMagArmorNormalizeCoeff = 4.0;
constexpr double kMagArmorMainPow = 0.7;

constexpr double kAttackSpeedDexterityCoeff = 3.0;
constexpr double kAttackSpeedStrengthCoeff = 1.0;
constexpr double kAttackSpeedIntelligenceCoeff = 1.0;

constexpr double kBaseDamageStrengthCoeff = 5.0;
constexpr double kBaseDamageDexterityCoeff = 1.0;
constexpr double kBaseDamageNormalizeCoeff = 6.0;

constexpr double kCritChanceLuckCoeff = 5.0;
constexpr double kCritChanceDexterityCoeff = 1.0;
constexpr double kCritChanceNormalizeCoeff = 8.0;
constexpr double kCritChanceMainPow = 0.8;

constexpr int const kExpForNextLevel[11] = {0,    10,   50,   100,   200,  500,
                                            1000, 2000, 5000, 10000, 20000};
constexpr int const kMaxLevel = 10;
} // namespace stat_const

#endif // ANTIPATTERNS_GAMEPLAYCONSTANTS_H
