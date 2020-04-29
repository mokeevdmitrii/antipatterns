//
// Created by dmitry on 4/21/20.
//

#include "Attribute.h"

BaseAttribute::BaseAttribute(Stats stats, LevelChange level_change) : _stats(stats), _level_change(level_change) {
    _current_value = _stats.base_value;
}

std::shared_ptr<BaseAttribute> BaseAttribute::Clone() const {
    std::shared_ptr<BaseAttribute> copy = std::make_shared<BaseAttribute>(_stats, _level_change);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->_current_value = _current_value;
    copy->_updated = _updated;
    return copy;
}

void BaseAttribute::AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus) {
    _raw_bonuses.push_back(std::move(raw_bonus));
}

void BaseAttribute::AddEffect(std::shared_ptr<BaseAttribute> effect) {
    _effects.push_back(std::move(effect));
}

void BaseAttribute::AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) {

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
}

void BaseAttribute::ResetUpdate() {
    _updated = false;
}

void BaseAttribute::UpdateLevel(int level_change) {
    _current_value = _stats.base_value;
    for (int i = 0; i < level_change; ++i) {
        _stats.base_value += _level_change.delta_value;
        _stats.base_value *= (1.0 + _level_change.multiplier);
    }
    Update(0);
}

void BaseAttribute::UpdateBaseValue(Stats delta_stats) {
    _stats.base_value += delta_stats.base_value;
    _stats.multiplier += delta_stats.multiplier;
}

void BaseAttribute::UpdateLevelChange(LevelChange delta_change) {
    _level_change.delta_value += delta_change.delta_value;
    _level_change.multiplier += _level_change.multiplier;
}


void BaseAttribute::SetCurrentValue(double value) {
    _current_value = value;
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


/// ----------------- RAW BONUS ----------------- ///

RawBonus::RawBonus(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change) {
    _id = id;
}


//actually this raw bonus has no chance to be removed, because all
// raw bonuses are removed from outside!
std::shared_ptr<BaseAttribute> RawBonus::Clone() const {
    std::shared_ptr<RawBonus> copy = std::make_shared<RawBonus>(_id, _stats, _level_change);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->_current_value = _current_value;
    copy->_updated = _updated;
    copy->_to_remove = _to_remove;
    return copy;
}

bool RawBonus::ToRemove() const {
    return _to_remove;
}

void RawBonus::SetAttributeId(ATTRIBUTE_ID id) {
    _id = id;
}

void RawBonus::SetToRemove(bool value) {
    _to_remove = value;
}



/// ---------------- EFFECT ------------------- ///

Effect::Effect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change), _id(id) {

}


void Effect::SetAttributeId(ATTRIBUTE_ID id) {
    _id = id;
}

std::shared_ptr<BaseAttribute> Effect::Clone() const {
    std::shared_ptr<Effect> copy = std::make_shared<Effect>(_id, _stats, _level_change);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->_current_value = _current_value;
    copy->_updated = _updated;
    return copy;
}

/// ---------------- OPERATING EFFECT ------------- ///

OperatingEffect::OperatingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : Effect(id, stats,
                                                                                                  level_change) {

}

std::shared_ptr<BaseAttribute> OperatingEffect::Clone() const {
    std::shared_ptr<OperatingEffect> copy = std::make_shared<OperatingEffect>(_id, _stats, _level_change);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->_current_value = _current_value;
    copy->_updated = _updated;
    copy->SetToRemove(_to_remove);
    return copy;
}

bool OperatingEffect::ToRemove() const {
    return _to_remove;
}

void OperatingEffect::SetToRemove(bool value) {
    _to_remove = value;
}

bool OperatingEffect::IsReady() const {
    _to_remove = true;
    return true;
}

/// -----------------TIMED EFFECT ------------------ ///

TimedEffect::TimedEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : Effect(id, stats, level_change) {

}

std::shared_ptr<BaseAttribute> TimedEffect::Clone() const {
    std::shared_ptr<TimedEffect> copy = std::make_shared<TimedEffect>(_id, _stats, _level_change);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->SetExpirationTime(_time_to_expire);
    copy->_updated = _updated;
    copy->_current_value = _current_value;
    return copy;
}


bool TimedEffect::ToRemove() const {
    return _time_to_expire <= 0;
}

void TimedEffect::Update(float time_elapsed) {
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
}

void TimedEffect::SetExpirationTime(float time_to_expire) {
    _time_to_expire = time_to_expire;
}


std::shared_ptr<Effect> CreateEffect(ATTRIBUTE_ID id, EFFECT_TYPE type, Stats stats, LevelChange level_change) {
    switch (type) {
        case EFFECT_TYPE::STATS:
            return std::make_shared<TimedEffect>(id, stats, level_change);
        case EFFECT_TYPE::POISON:
            return std::make_shared<ProckingEffect>(ATTRIBUTE_ID::CURR_HP, stats, level_change);
        case EFFECT_TYPE::PHYSICAL_DAMAGE:
            return std::make_shared<OperatingEffect>(ATTRIBUTE_ID::CURR_HP, stats, level_change);
        case EFFECT_TYPE::MAGICAL_DAMAGE:
            return std::make_shared<OperatingEffect>(ATTRIBUTE_ID::CURR_HP, stats, level_change);
    }
}

/// --------------OVER_TIME_EFFECT ------------///

OverTimeEffect::OverTimeEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : TimedEffect(id, stats,
                                                                                                     level_change) {

}

std::shared_ptr<BaseAttribute> OverTimeEffect::Clone() const {
    std::shared_ptr<OverTimeEffect> copy = std::make_shared<OverTimeEffect>(_id, _stats, _level_change);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->SetExpirationTime(_time_to_expire);
    copy->_current_value = _current_value;
    copy->_updated = _updated;
    copy->SetTickTime(_tick_time);
    copy->SetTimeFromTick(_time_from_tick);
    return copy;
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
}

void OverTimeEffect::SetTickTime(float tick_time) {
    _tick_time = tick_time;
}

void OverTimeEffect::SetTimeFromTick(float time_from_tick) {
    _time_from_tick = time_from_tick;
}


/// --------------- PROCKING_EFFECT ------------ ///

ProckingEffect::ProckingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : OverTimeEffect(id, stats,
                                                                                                        level_change) {

}

std::shared_ptr<BaseAttribute> ProckingEffect::Clone() const {
    return OverTimeEffect::Clone();
}

bool ProckingEffect::IsReady() const {
    if (_time_from_tick >= _tick_time) {
        _time_from_tick -= _tick_time;
        return true;
    }
    return false;
}


/// ---------------- ATTRIBUTE ---------------- ///


Attribute::Attribute(Stats stats, LevelChange level_change, StatsFunc calc_func)
        : BaseAttribute(stats, level_change),
          _calc_func(std::move(calc_func)) {
}

void Attribute::AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) {
    _base_attributes[id] = std::move(attribute);
}


void Attribute::Update(float time_elapsed) {
    if (_updated) {
        return;
    }
    _updated = true;
    _current_value = _stats.base_value;
    ApplyBaseAttributes(_base_attributes, _current_value);
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
}

void Attribute::ApplyBaseAttributes(const BaseStats &base_attributes, double &base_value) {
    base_value += _calc_func(base_attributes);
}

//DONT COPY BASE ATTRIBUTES PLEASE!!!!!!!!!!!!!!!!!!
std::shared_ptr<BaseAttribute> Attribute::Clone() const {
    std::shared_ptr<Attribute> copy = std::make_shared<Attribute>(_stats, _level_change, _calc_func);
    for (const auto &raw_bonus : _raw_bonuses) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : _effects) {
        effect->AddEffect(effect->Clone());
    }
    copy->_current_value = _current_value;
    copy->_updated = _updated;
    copy->_calc_func = _calc_func;
    return copy;
}



/// ------------ ATTRIBUTE VALUE ------------ ///

AttributeValue::AttributeValue(std::shared_ptr<BaseAttribute> max_value, double relative_value) : _max_value(
        std::move(max_value)), _relative_value(relative_value), BaseAttribute(Stats(), LevelChange()) {

}

std::shared_ptr<BaseAttribute> AttributeValue::Clone() const {
    return std::make_shared<AttributeValue>(nullptr, _relative_value);
}

void AttributeValue::AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) {
    _max_value = std::move(attribute);
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
}

void AttributeValue::UpdateLevel(int level_change) {
    _relative_value = 1;
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


