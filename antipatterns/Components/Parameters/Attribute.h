//
// Created by dmitry on 4/21/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTE_H
#define ANTIPATTERNS_ATTRIBUTE_H



#include <list>
#include <set>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <functional>

enum class ATTRIBUTE_ID {
    VIGOR,
    STRENGTH,
    DEXTERITY,
    INTELLIGENCE,
    FAITH,
    LUCK,
    MAX_HP,
    MAX_MANA,
    PHYS_ARMOR,
    MAG_ARMOR,
    ATTACK_SPEED,
    BASE_DAMAGE,
    CRIT_CHANCE,
    CURR_HP,
    CURR_MANA
};

struct Stats {
    double base_value;
    double multiplier;

    Stats() = default;
    Stats(double base_value, double multiplier) : base_value(base_value), multiplier(multiplier) {}
};

struct LevelChange {
    double delta_value;
    double multiplier;

    LevelChange() = default;
    LevelChange(double delta_value, double multiplier) : delta_value(delta_value), multiplier(multiplier) {}
};

class BaseAttribute {
public:
    //BaseAttribute() = default;

    explicit BaseAttribute(Stats stats, LevelChange level_change);

    BaseAttribute(const BaseAttribute& other) = delete;
    BaseAttribute& operator = (const BaseAttribute& other) = delete;

    virtual std::shared_ptr<BaseAttribute> Clone() const;

    void AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus);

    void AddEffect(std::shared_ptr<BaseAttribute> effect);

    virtual void AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute);

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

    void SetCurrentValue(double value);

protected:
    virtual void UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>> &bonuses);

    std::list<std::shared_ptr<BaseAttribute>> _raw_bonuses{};
    std::list<std::shared_ptr<BaseAttribute>> _effects{};
    Stats _stats;
    LevelChange _level_change;
    double _current_value;
    bool _updated{false};
private:
};

class RawBonus : public BaseAttribute {
public:
    explicit RawBonus(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    bool ToRemove() const override;

    void SetAttributeId(ATTRIBUTE_ID id);

    void SetToRemove(bool value);

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

    std::shared_ptr<BaseAttribute> Clone() const override;

    void SetAttributeId(ATTRIBUTE_ID id);

protected:
    ATTRIBUTE_ID _id;
};

class OperatingEffect : public Effect {
public:
    OperatingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    bool ToRemove() const override;

    void SetToRemove(bool value);

    bool IsReady() const override;

protected:
    mutable bool _to_remove{false};
};


class TimedEffect : public Effect {
public:
    TimedEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

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

    std::shared_ptr<BaseAttribute> Clone() const override;

    void Update(float time_elapsed) override;

    void SetTickTime(float tick_time);

protected:
    void SetTimeFromTick(float time_from_tick);

    float _tick_time{1.0};
    mutable float _time_from_tick{0};
};

class ProckingEffect : public OverTimeEffect {
public:
    ProckingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change);

    std::shared_ptr<BaseAttribute> Clone() const override;

    //очень осторожно - возвращает IsReady() == true всего один раз !!!
    bool IsReady() const override;
};

std::shared_ptr<Effect> CreateEffect(ATTRIBUTE_ID id, EFFECT_TYPE type, Stats stats, LevelChange level_change);

/* каждый атрибут может зависеть от остальных атрибутов,
 * к нему применяются первоначальные бонусы (одежда и т.д.),
 * затем применяются остальные бонусы */
class Attribute : public BaseAttribute {
public:
    using BaseStats = std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>>;
    using StatsFunc = std::function<double(const std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>>&)>;

    Attribute(Stats stats, LevelChange level_change, StatsFunc calc_func);

    std::shared_ptr<BaseAttribute> Clone() const override;

    void AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) override;

    void Update(float time_elapsed) override;
protected:
    void ApplyBaseAttributes(const BaseStats& base_attributes, double& base_value);

    std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>> _base_attributes;
    StatsFunc _calc_func;
private:

};

//хихихихи максируемся под BaseAttribute, но полностью меняем интерфейс!!!
class AttributeValue : public BaseAttribute {
public:
    AttributeValue() = default;

    explicit AttributeValue(std::shared_ptr<BaseAttribute> max_value, double relative_value = 1);

    std::shared_ptr<BaseAttribute> Clone() const override;

    void AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) override;

    double GetBaseValue() const override;

    double GetCurrentValue() const override;

    double GetMultiplier() const override;

    void Update(float time_elapsed) override;

    //здоровье обновляется при получении уровня
    void UpdateLevel(int level_change) override;

protected:
    void UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>>& bonuses) override;
    std::shared_ptr<BaseAttribute> _max_value;
    double _relative_value;
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
