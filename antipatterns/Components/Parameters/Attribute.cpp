//
// Created by dmitry on 4/21/20.
//

#include "Attribute.h"

BaseAttribute::BaseAttribute(Stats stats, LevelChange level_change) : _stats(stats), _level_change(level_change) {

}

void BaseAttribute::AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus) {
    _raw_bonuses.push_back(std::move(raw_bonus));
}

void BaseAttribute::AddEffect(std::shared_ptr<BaseAttribute> effect) {
    _effects.push_back(std::move(effect));
}

void BaseAttribute::UpdateBaseValue(double delta_value) {
    _stats.base_value += delta_value;
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
    _current_value = _stats.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
    //смотрим не вышли ли за допустимые границы
    CheckBoundaries();
}

void BaseAttribute::UpdateLevel(int level_change) {
    for (int i = 0; i < level_change; ++i) {
        _stats.base_value += _level_change.delta_value;
        _stats.base_value *= (1.0 + _level_change.multiplier);
    }
}

void BaseAttribute::ApplyBonus(std::shared_ptr<BaseAttribute> &base_attribute, Stats stats) {

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

Effect::Effect(EFFECT_TYPE type, Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change), _type(type) {

}

bool Effect::ToRemove() const {
    return _time_to_expire <= 0;
}

void Effect::Update(float time_elapsed) {
    _time_to_expire -= time_elapsed;
    BaseAttribute::Update(time_elapsed);
}

void Effect::SetExpirationTime(float time_to_expire) {
    _time_to_expire = time_to_expire;
}

void Effect::SetAttributeId(ATTRIBUTE_ID id) {
    _id = id;
}

/// ---------------- ATTRIBUTE ---------------- ///


template<typename... Attributes>
Attribute::Attribute(Stats stats, LevelChange level_change, Attributes... attributes) : BaseAttribute(stats, level_change) {
    VariadicConstruct(attributes...);
}

Attribute::Attribute(Stats stats, LevelChange level_change, std::vector<std::shared_ptr<BaseAttribute>> attributes) : BaseAttribute(stats, level_change),
                                                                                            _base_attributes(std::move(
                                                                                                    attributes)) {
}

template<typename... Attributes>
void Attribute::VariadicConstruct(std::shared_ptr<BaseAttribute> stat, Attributes... attributes) {
    _base_attributes.push_back(std::move(stat));
}

void Attribute::VariadicConstruct() {}

void Attribute::Update(float time_elapsed) {
    _current_value = _stats.base_value;
    ApplyBaseAttributes(_stats.base_value);
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, _raw_bonuses);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, _effects);
    //смотрим не вышли ли за допустимые границы
    CheckBoundaries();
}

/// ------------------ STRENGTH ------------------ ///

