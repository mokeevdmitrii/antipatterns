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

    virtual void UpdateLevel(int level_change);

    void UpdateBaseValue(double delta_value);

    void UpdateLevelChange(LevelChange delta_change);

protected:
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
    OverTimeEffect(EFFECT_TYPE type, Stats stats, LevelChange level_change) : Effect(type, stats, level_change) {

    }

    void Update(float time_elapsed) override {
        _time_from_tick += time_elapsed;
        Effect::Update(time_elapsed);
    }

    void SetTickTime(float tick_time) {
        _tick_time = tick_time;
    }

protected:
    float _tick_time{1.0};
    mutable float _time_from_tick{0};
};

class ProckingEffect : public OverTimeEffect {
public:
    ProckingEffect(EFFECT_TYPE type, Stats stats, LevelChange level_change) : OverTimeEffect(type, stats, level_change) {

    }

    //очень осторожно - возвращает IsReady() == true всего один раз !!!
    bool IsReady() const override {
        if (_time_from_tick >= _tick_time) {
            _time_from_tick -= _tick_time;
            return true;
        }
        return false;
    }
};

std::shared_ptr<Effect> CreateEffect(EFFECT_TYPE type, Stats stats, LevelChange level_change);

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

//хихихихи максируемся под BaseAttribute, но полностью меняем интерфейс!!!
class AttributeValue : public BaseAttribute {
public:
    AttributeValue(std::shared_ptr<BaseAttribute> max_value) : _max_value(std::move(max_value)), BaseAttribute(Stats(), LevelChange()) {

    }

    double GetBaseValue() const override {
        return _max_value->GetBaseValue();
    }

    double GetCurrentValue() const override {
        return _max_value->GetCurrentValue() * _relative_value;
    }

    double GetMultiplier() const override {
        return _max_value->GetMultiplier();
    }

    void Update(float time_elapsed) override {
        //я тут
    }


protected:
    void UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>>& bonuses) override {
        auto b_it = bonuses.begin();
        double bonus_value{0}, bonus_multiplier{0};
        while (b_it != bonuses.end()) {
            //порядок - подумать!!!!
            (*b_it)->Update(time_elapsed);
            if ((*b_it)->ToRemove()) {
                b_it = bonuses.erase(b_it);
                continue;
            }
            if ((*b_it)->IsReady()) {
                bonus_value += (*b_it)->GetCurrentValue();
                bonus_multiplier += (*b_it)->GetMultiplier();
            }
            ++b_it;
        }
        _relative_value += bonus_value / _max_value->GetCurrentValue();
        _relative_value *= (1.0 + bonus_multiplier);
    }

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
