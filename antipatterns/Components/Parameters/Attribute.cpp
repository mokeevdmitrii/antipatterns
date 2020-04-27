//
// Created by dmitry on 4/21/20.
//

#include "Attribute.h"

BaseAttribute::BaseAttribute(Stats stats, LevelChange level_change) : _stats(stats), _level_change(level_change) {
    _current_value = _stats.base_value;
}

void BaseAttribute::AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus) {
    _raw_bonuses.push_back(std::move(raw_bonus));
}

void BaseAttribute::AddEffect(std::shared_ptr<BaseAttribute> effect) {
    _effects.push_back(std::move(effect));
}

void BaseAttribute::UpdateBaseValue(Stats delta_stats) {
    _stats.base_value += delta_stats.base_value;
    _stats.multiplier += delta_stats.multiplier;
}

void BaseAttribute::UpdateLevelChange(LevelChange delta_change) {
    _level_change.delta_value += delta_change.delta_value;
    _level_change.multiplier += _level_change.multiplier;
}

double BaseAttribute::GetBaseValue() const {
    return _stats.base_value;
}

double BaseAttribute::GetCurrentValue() const {
    return _current_value;
}

double BaseAttribute::GetMultiplier() const {
    return _stats.multiplier;
}

bool BaseAttribute::IsReady() const {
    return true;
}

bool BaseAttribute::ToRemove() const {
    return false;
}

void BaseAttribute::Update(float time_elapsed) {
    if (_updated) {
        return;
    }
    _updated = true;
    _current_value = _stats.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
    //смотрим не вышли ли за допустимые границы
    CheckBoundaries();
}

void BaseAttribute::UpdateLevel(int level_change) {
    _current_value = _stats.base_value;
    for (int i = 0; i < level_change; ++i) {
        _stats.base_value += _level_change.delta_value;
        _stats.base_value *= (1.0 + _level_change.multiplier);
    }
    Update(0);
}


void BaseAttribute::UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>> &bonuses) {
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
    _current_value += bonus_value;
    _current_value *= (1.0 + bonus_multiplier);
}

void BaseAttribute::CheckBoundaries() {
    if (_current_value * _stats.base_value < 0) {
        _current_value = 0;
    }
}

void BaseAttribute::ResetUpdate() {
    _updated = false;
}

/// ----------------- RAW BONUS ----------------- ///


RawBonus::RawBonus(Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change) {

}

bool RawBonus::ToRemove() const {
    return _to_remove;
}

void RawBonus::SetAttributeId(ATTRIBUTE_ID id) {
    _id = id;
}

void RawBonus::SetToRemove() {
    _to_remove = true;
}


/// ----------------- EFFECT ------------------ ///

Effect::Effect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : _id(id), BaseAttribute(stats, level_change) {

}

bool Effect::ToRemove() const {
    return _time_to_expire <= 0;
}

void Effect::Update(float time_elapsed) {
    if (_updated) {
        return;
    }
    _time_to_expire -= time_elapsed;
    _updated = true;
    _current_value = _stats.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
    //смотрим не вышли ли за допустимые границы
    CheckBoundaries();
}

void Effect::SetExpirationTime(float time_to_expire) {
    _time_to_expire = time_to_expire;
}

void Effect::SetAttributeId(ATTRIBUTE_ID id) {
    _id = id;
}


std::shared_ptr<Effect> CreateEffect(EFFECT_TYPE type, Stats stats, LevelChange level_change) {
    switch (type) {
        case EFFECT_TYPE::STATS:
            return std::shared_ptr<Effect>(t)
            break;
        case EFFECT_TYPE::POISON:
            break;
        case EFFECT_TYPE::DAMAGE:
            break;
    }
}

/// --------------OVER_TIME_EFFECT ------------///

OverTimeEffect::OverTimeEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : Effect(id, stats,
                                                                                                 level_change) {

}

void OverTimeEffect::Update(float time_elapsed) {
    if (_updated) {
        return;
    }
    _time_from_tick += time_elapsed;
    _time_to_expire -= time_elapsed;
    _updated = true;
    _current_value = _stats.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
    //смотрим не вышли ли за допустимые границы
    CheckBoundaries();
}

void OverTimeEffect::SetTickTime(float tick_time) {
    _tick_time = tick_time;
}

/// --------------- PROCKING_EFFECT ------------ ///

ProckingEffect::ProckingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : OverTimeEffect(id, stats,
                                                                                                         level_change) {

}

bool ProckingEffect::IsReady() const {
    if (_time_from_tick >= _tick_time) {
        _time_from_tick -= _tick_time;
        return true;
    }
    return false;
}


/// ---------------- ATTRIBUTE ---------------- ///


template<typename... Attributes>
Attribute::Attribute(Stats stats, LevelChange level_change, Attributes... attributes) : BaseAttribute(stats,
                                                                                                      level_change) {
    VariadicConstruct(attributes...);
}

Attribute::Attribute(Stats stats, LevelChange level_change, std::vector<std::shared_ptr<BaseAttribute>> attributes)
        : BaseAttribute(stats, level_change),
          _base_attributes(std::move(
                  attributes)) {
}

template<typename... Attributes>
void Attribute::VariadicConstruct(std::shared_ptr<BaseAttribute> stat, Attributes... attributes) {
    _base_attributes.push_back(std::move(stat));
    VariadicConstruct(attributes...);
}

void Attribute::VariadicConstruct() {}

void Attribute::Update(float time_elapsed) {
    if (_updated) {
        return;
    }
    _updated = true;
    _current_value = _stats.base_value;
    ApplyBaseAttributes(_stats.base_value);
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
    //смотрим не вышли ли за допустимые границы
    CheckBoundaries();
}

/// ------------ ATTRIBUTE VALUE ------------ ///

AttributeValue::AttributeValue(std::shared_ptr<BaseAttribute> max_value) : _max_value(std::move(max_value)),
                                                                           BaseAttribute(Stats(), LevelChange()) {

}

double AttributeValue::GetBaseValue() const {
    return _max_value->GetBaseValue();
}

double AttributeValue::GetCurrentValue() const {
    return _max_value->GetCurrentValue() * _relative_value;
}

double AttributeValue::GetMultiplier() const {
    return _max_value->GetMultiplier();
}

void AttributeValue::Update(float time_elapsed) {
    if (_updated) {
        return;
    }
    _updated = true;
    UpdateBonuses(time_elapsed, _raw_bonuses);
    UpdateBonuses(time_elapsed, _effects);
    CheckBoundaries();
}

void AttributeValue::UpdateLevel(int level_change) {
    _relative_value = 1;
}

void AttributeValue::CheckBoundaries() {
    if (_relative_value < 0) {
        _relative_value = 0;
    } else if (_relative_value > 1) {
        _relative_value = 1;
    }
}

void AttributeValue::UpdateBonuses(float time_elapsed, std::list<std::shared_ptr<BaseAttribute>> &bonuses) {
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

/// ---------- CONCRETE ATTRIBUTES ---------- ///
