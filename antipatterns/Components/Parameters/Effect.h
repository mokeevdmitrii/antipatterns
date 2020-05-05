//
// Created by dmitry on 4/21/20.
//

#ifndef ANTIPATTERNS_EFFECT_H
#define ANTIPATTERNS_EFFECT_H

#include "Attribute.h"

enum class EFFECT_TYPE {
    STATS,
    POISON,
    PHYSICAL_DAMAGE,
    MAGICAL_DAMAGE
};

class Effect : public BaseAttribute {
public:
    Effect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    ATTRIBUTE_ID GetAttributeid() const;

    void SetAttributeId(ATTRIBUTE_ID id);

protected:
    ATTRIBUTE_ID id_;
};

class OperatingEffect : public Effect {
public:
    OperatingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    bool ToRemove() const override;

    void SetToRemove(bool value);

    bool IsReady() const override;

protected:
    mutable bool to_remove_{false};
};


class TimedEffect : public Effect {
public:
    TimedEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    bool ToRemove() const override;

    void Update(float time_elapsed) override;

    void SetExpirationTime(float time_to_expire);

protected:
    float time_to_expire_{std::numeric_limits<float>::infinity()};
private:
};


class OverTimeEffect : public TimedEffect {
public:
    OverTimeEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    void Update(float time_elapsed) override;

    void SetTickTime(float tick_time);

protected:
    void SetTimeFromTick(float time_from_tick);

    float tick_time_{1.0};
    mutable float time_from_tick_{0};
};

class ProckingEffect : public OverTimeEffect {
public:
    ProckingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    bool IsReady() const override;
};

std::shared_ptr<Effect> CreateEffect(ATTRIBUTE_ID id, EFFECT_TYPE type, Stats stats, LevelChange level_change);


#endif //ANTIPATTERNS_EFFECT_H
