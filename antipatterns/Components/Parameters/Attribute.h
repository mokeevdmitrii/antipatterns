//
// Created by dmitry on 4/21/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTE_H
#define ANTIPATTERNS_ATTRIBUTE_H



#include "Expression.h"

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

class BaseAttribute : public Value {
public:
    //BaseAttribute() = default;

    explicit BaseAttribute(Stats stats, LevelChange level_change);

    void AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus);

    void AddEffect(std::shared_ptr<BaseAttribute> effect);

    virtual double GetBaseValue() const;

    virtual double GetCurrentValue() const;

    virtual double GetMultiplier() const;

    virtual bool IsReady() const;

    virtual bool ToRemove() const;

    virtual void Update(float time_elapsed);

    void ResetUpdate();

    virtual void UpdateLevel(int level_change);

    void UpdateBaseValue(Stats delta_stats);

    void UpdateLevelChange(LevelChange delta_change);

protected:
    virtual void UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>> &bonuses);

    virtual void CheckBoundaries();

    std::list<std::shared_ptr<BaseAttribute>> _raw_bonuses{};
    std::list<std::shared_ptr<BaseAttribute>> _effects{};
    Stats _stats;
    LevelChange _level_change;
    bool _updated{false};
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
    POISON,
    PHYSICAL_DAMAGE,
    MAGICAL_DAMAGE
};

class Effect : public BaseAttribute {
public:
    Effect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    void SetAttributeId(ATTRIBUTE_ID id);

protected:
    ATTRIBUTE_ID _id;
};


class TimedEffect : public Effect {
public:
    TimedEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    bool ToRemove() const override;

    void Update(float time_elapsed) override;

    void SetExpirationTime(float time_to_expire);

protected:
    float _time_to_expire{std::numeric_limits<float>::infinity()};
private:
};


class OverTimeEffect : public TimedEffect {
public:
    OverTimeEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    void Update(float time_elapsed) override;

    void SetTickTime(float tick_time);

protected:
    float _tick_time{1.0};
    mutable float _time_from_tick{0};
};

class ProckingEffect : public OverTimeEffect {
public:
    ProckingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    //очень осторожно - возвращает IsReady() == true всего один раз !!!
    bool IsReady() const override;
};

std::shared_ptr<TimedEffect> CreateEffect(EFFECT_TYPE type, Stats stats, LevelChange level_change);

/* каждый атрибут может зависеть от остальных атрибутов,
 * к нему применяются первоначальные бонусы (одежда и т.д.),
 * затем применяются остальные бонусы */
class Attribute : public BaseAttribute {
public:
    Attribute(Stats stats, LevelChange level_change, std::shared_ptr<Expression> expression);

    void Update(float time_elapsed) override;
protected:
    virtual void ApplyBaseAttributes(double& base_value) = 0;

    /// СЮДА СМОТРИ ДИМА МОКЕЕВ ТЫ СЕЙЧАС ДЕЛАЕШЬ ЭТО ///

    std::shared_ptr<Expression> _expression;
private:
    void UpdateBaseAttributes(float time_elapsed);
};

//хихихихи максируемся под BaseAttribute, но полностью меняем интерфейс!!!
class AttributeValue : public BaseAttribute {
public:
    AttributeValue() = default;

    explicit AttributeValue(std::shared_ptr<BaseAttribute> max_value);

    double GetBaseValue() const override;

    double GetCurrentValue() const override;

    double GetMultiplier() const override;

    void Update(float time_elapsed) override;

    //здоровье обновляется при получении уровня
    void UpdateLevel(int level_change) override;

    void CheckBoundaries() override;
protected:
    void UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>>& bonuses) override;
    std::shared_ptr<BaseAttribute> _max_value;
    double _relative_value{1};
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
