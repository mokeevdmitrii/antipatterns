//
// Created by dmitry on 4/21/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTE_H
#define ANTIPATTERNS_ATTRIBUTE_H

#include <list>
#include <memory>
#include <vector>

enum class ATTRIBUTE_ID {
    STRENGTH
};

struct Stats {
    double base_value;
    double multiplier;
};

struct LevelChange {
    double delta_value;
    double multiplier;
};

class BaseAttribute {
public:
    //BaseAttribute() = default;

    explicit BaseAttribute(Stats stats, LevelChange level_change);

    virtual ~BaseAttribute() = default;

    void AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus);

    void AddEffect(std::shared_ptr<BaseAttribute> effect);

    virtual double GetBaseValue() const;

    virtual double GetCurrentValue() const;

    virtual double GetMultiplier() const;

    virtual bool IsReady() const;

    virtual bool ToRemove() const;

    virtual void Update(float time_elapsed);

    virtual void UpdateLevel(int level_change = 1);

    void UpdateBaseValue(double delta_value);

    void UpdateLevelChange(LevelChange delta_change);

protected:
    virtual void ApplyBonus(std::shared_ptr<BaseAttribute>& base_attribute, Stats stats);

    virtual void UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>> &bonuses);

    virtual void CheckBoundaries();

    LevelChange _level_change;
    std::list<std::shared_ptr<BaseAttribute>> _raw_bonuses;
    std::list<std::shared_ptr<BaseAttribute>> _effects;
    Stats _stats;
    double _current_value;
private:

};

class RawBonus : public BaseAttribute {
public:
    explicit RawBonus(Stats stats, LevelChange level_change);

    bool ToRemove() const override;

    void SetAttributeId(ATTRIBUTE_ID id);

    void SetToRemove();

private:
    bool _to_remove{false};
    ATTRIBUTE_ID _id;
};

enum class EFFECT_TYPE {
    STATS,
    POISON
};

class Effect : public BaseAttribute {
public:
    Effect(EFFECT_TYPE type, Stats stats, LevelChange level_change);

    bool ToRemove() const override;

    void Update(float time_elapsed) override;

    void SetExpirationTime(float time_to_expire);

    void SetAttributeId(ATTRIBUTE_ID id);

private:
    EFFECT_TYPE _type;
    ATTRIBUTE_ID _id;
    float _time_to_expire{std::numeric_limits<float>::infinity()};
};


class OverTimeEffect : public Effect {
public:
    OverTimeEffect(EFFECT_TYPE type, Stats stats, LevelChange level_change) : Effect(type, stats, _level_change) {

    }

    


    void SetTickTime(float tick_time) {
        _tick_time = tick_time;
    }

private:
    float _tick_time{1.0};
    mutable float _time_from_tick;
};

std::shared_ptr<Effect> CreateEffect(EFFECT_TYPE type);

/* каждый атрибут может зависеть от остальных атрибутов,
 * к нему применяются первоначальные бонусы (одежда и т.д.),
 * затем применяются остальные бонусы */
class Attribute : public BaseAttribute {
public:
    template<typename ...Attributes>
    explicit Attribute(Stats stats, LevelChange level_change, Attributes... attributes);

    Attribute(Stats stats, LevelChange level_change, std::vector<std::shared_ptr<BaseAttribute>> attributes);

    void Update(float time_elapsed) override;
private:
    virtual void ApplyBaseAttributes(double& base_value) = 0;

    template<typename ...Attributes>
    void VariadicConstruct(std::shared_ptr<BaseAttribute> stat, Attributes... attributes);

    void VariadicConstruct();

    std::vector<std::shared_ptr<BaseAttribute>> _base_attributes;
};

class AttributeValue : public BaseAttribute {
public:
    AttributeValue(std::shared_ptr<BaseAttribute> max_value) : _max_value(std::move(max_value)), BaseAttribute(Stats(), LevelChange()) {

    }




private:
    std::shared_ptr<BaseAttribute> _max_value;
    double relative_value{1};
};




//типы базовых атрибутов:

// живучесть
// сила
// ловкость
// интеллект
// вера
// удача


// типы производных атрибутов:

// максимальное здоровье
// максимальная мана
// стандартный урон (с руки)
// скорость атаки
// шанс критического удара
// защита
// магическая защита



#endif //ANTIPATTERNS_ATTRIBUTE_H
