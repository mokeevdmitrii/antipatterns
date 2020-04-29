//
// Created by dmitry on 4/21/20.
//

#include "Attribute.h"

BaseAttribute::BaseAttribute(Stats stats, LevelChange level_change) : stats_(stats), level_change_(level_change) {
    current_value_ = stats_.base_value;
}

std::shared_ptr<BaseAttribute> BaseAttribute::Clone() const {
    std::shared_ptr<BaseAttribute> copy = std::make_shared<BaseAttribute>(stats_, level_change_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->current_value_ = current_value_;
    copy->updated_ = updated_;
    return copy;
}

void BaseAttribute::AddRawBonus(std::shared_ptr<BaseAttribute> raw_bonus) {
    raw_bonuses_.push_back(std::move(raw_bonus));
}

void BaseAttribute::AddEffect(std::shared_ptr<BaseAttribute> effect) {
    effects_.push_back(std::move(effect));
}

void BaseAttribute::AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) {

}

double BaseAttribute::GetBaseValue() const {
    return stats_.base_value;
}

double BaseAttribute::GetCurrentValue() const {
    return current_value_;
}

double BaseAttribute::GetMultiplier() const {
    return stats_.multiplier;
}

bool BaseAttribute::IsReady() const {
    return true;
}

bool BaseAttribute::ToRemove() const {
    return false;
}

void BaseAttribute::Update(float time_elapsed) {
    if (updated_) {
        return;
    }
    updated_ = true;
    current_value_ = stats_.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, raw_bonuses_);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, effects_);
}

void BaseAttribute::ResetUpdate() {
    updated_ = false;
}

void BaseAttribute::UpdateLevel(int level_change) {
    current_value_ = stats_.base_value;
    for (int i = 0; i < level_change; ++i) {
        stats_.base_value += level_change_.delta_value;
        stats_.base_value *= (1.0 + level_change_.multiplier);
    }
    Update(0);
}

void BaseAttribute::UpdateBaseValue(Stats delta_stats) {
    stats_.base_value += delta_stats.base_value;
    stats_.multiplier += delta_stats.multiplier;
}

void BaseAttribute::UpdateLevelChange(LevelChange delta_change) {
    level_change_.delta_value += delta_change.delta_value;
    level_change_.multiplier += level_change_.multiplier;
}


void BaseAttribute::SetCurrentValue(double value) {
    current_value_ = value;
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
    current_value_ += bonus_value;
    current_value_ *= (1.0 + bonus_multiplier);
}


/// ----------------- RAW BONUS ----------------- ///

RawBonus::RawBonus(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change) {
    id_ = id;
}


//actually this raw bonus has no chance to be removed, because all
// raw bonuses are removed from outside!
std::shared_ptr<BaseAttribute> RawBonus::Clone() const {
    std::shared_ptr<RawBonus> copy = std::make_shared<RawBonus>(id_, stats_, level_change_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->current_value_ = current_value_;
    copy->updated_ = updated_;
    copy->to_remove_ = to_remove_;
    return copy;
}

bool RawBonus::ToRemove() const {
    return to_remove_;
}

void RawBonus::SetAttributeId(ATTRIBUTE_ID id) {
    id_ = id;
}

void RawBonus::SetToRemove(bool value) {
    to_remove_ = value;
}



/// ---------------- EFFECT ------------------- ///

Effect::Effect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change), id_(id) {

}


void Effect::SetAttributeId(ATTRIBUTE_ID id) {
    id_ = id;
}

std::shared_ptr<BaseAttribute> Effect::Clone() const {
    std::shared_ptr<Effect> copy = std::make_shared<Effect>(id_, stats_, level_change_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->current_value_ = current_value_;
    copy->updated_ = updated_;
    return copy;
}

/// ---------------- OPERATING EFFECT ------------- ///

OperatingEffect::OperatingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : Effect(id, stats,
                                                                                                  level_change) {

}

std::shared_ptr<BaseAttribute> OperatingEffect::Clone() const {
    std::shared_ptr<OperatingEffect> copy = std::make_shared<OperatingEffect>(id_, stats_, level_change_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->current_value_ = current_value_;
    copy->updated_ = updated_;
    copy->SetToRemove(to_remove_);
    return copy;
}

bool OperatingEffect::ToRemove() const {
    return to_remove_;
}

void OperatingEffect::SetToRemove(bool value) {
    to_remove_ = value;
}

bool OperatingEffect::IsReady() const {
    to_remove_ = true;
    return true;
}

/// -----------------TIMED EFFECT ------------------ ///

TimedEffect::TimedEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : Effect(id, stats, level_change) {

}

std::shared_ptr<BaseAttribute> TimedEffect::Clone() const {
    std::shared_ptr<TimedEffect> copy = std::make_shared<TimedEffect>(id_, stats_, level_change_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->SetExpirationTime(time_to_expire_);
    copy->updated_ = updated_;
    copy->current_value_ = current_value_;
    return copy;
}


bool TimedEffect::ToRemove() const {
    return time_to_expire_ <= 0;
}

void TimedEffect::Update(float time_elapsed) {
    if (updated_) {
        return;
    }
    time_to_expire_ -= time_elapsed;
    updated_ = true;
    current_value_ = stats_.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, raw_bonuses_);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, effects_);
}

void TimedEffect::SetExpirationTime(float time_to_expire) {
    time_to_expire_ = time_to_expire;
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
    std::shared_ptr<OverTimeEffect> copy = std::make_shared<OverTimeEffect>(id_, stats_, level_change_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->SetExpirationTime(time_to_expire_);
    copy->current_value_ = current_value_;
    copy->updated_ = updated_;
    copy->SetTickTime(tick_time_);
    copy->SetTimeFromTick(time_from_tick_);
    return copy;
}

void OverTimeEffect::Update(float time_elapsed) {
    if (updated_) {
        return;
    }
    time_from_tick_ += time_elapsed;
    time_to_expire_ -= time_elapsed;
    updated_ = true;
    current_value_ = stats_.base_value;
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, raw_bonuses_);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, effects_);
}

void OverTimeEffect::SetTickTime(float tick_time) {
    tick_time_ = tick_time;
}

void OverTimeEffect::SetTimeFromTick(float time_from_tick) {
    time_from_tick_ = time_from_tick;
}


/// --------------- PROCKING_EFFECT ------------ ///

ProckingEffect::ProckingEffect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : OverTimeEffect(id, stats,
                                                                                                        level_change) {

}

std::shared_ptr<BaseAttribute> ProckingEffect::Clone() const {
    return OverTimeEffect::Clone();
}

bool ProckingEffect::IsReady() const {
    if (time_from_tick_ >= tick_time_) {
        time_from_tick_ -= tick_time_;
        return true;
    }
    return false;
}


/// ---------------- ATTRIBUTE ---------------- ///


Attribute::Attribute(Stats stats, LevelChange level_change, StatsFunc calc_func)
        : BaseAttribute(stats, level_change),
          calc_func_(std::move(calc_func)) {
}

void Attribute::AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) {
    base_attributes_[id] = std::move(attribute);
}


void Attribute::Update(float time_elapsed) {
    if (updated_) {
        return;
    }
    updated_ = true;
    current_value_ = stats_.base_value;
    ApplyBaseAttributes(base_attributes_, current_value_);
    //обновляем все постоянные бонусы
    UpdateBonuses(time_elapsed, raw_bonuses_);
    //обновляем все эффекты
    UpdateBonuses(time_elapsed, effects_);
}

void Attribute::ApplyBaseAttributes(const BaseStats &base_attributes, double &base_value) {
    base_value += calc_func_(base_attributes);
}

//DONT COPY BASE ATTRIBUTES PLEASE!!!!!!!!!!!!!!!!!!
std::shared_ptr<BaseAttribute> Attribute::Clone() const {
    std::shared_ptr<Attribute> copy = std::make_shared<Attribute>(stats_, level_change_, calc_func_);
    for (const auto &raw_bonus : raw_bonuses_) {
        copy->AddRawBonus(raw_bonus->Clone());
    }
    for (const auto &effect : effects_) {
        effect->AddEffect(effect->Clone());
    }
    copy->current_value_ = current_value_;
    copy->updated_ = updated_;
    copy->calc_func_ = calc_func_;
    return copy;
}



/// ------------ ATTRIBUTE VALUE ------------ ///

AttributeValue::AttributeValue(std::shared_ptr<BaseAttribute> max_value, double relative_value) : max_value_(
        std::move(max_value)), relative_value_(relative_value), BaseAttribute(Stats(), LevelChange()) {

}

std::shared_ptr<BaseAttribute> AttributeValue::Clone() const {
    return std::make_shared<AttributeValue>(nullptr, relative_value_);
}

void AttributeValue::AddDependantAttribute(ATTRIBUTE_ID id, std::shared_ptr<BaseAttribute> attribute) {
    max_value_ = std::move(attribute);
}

double AttributeValue::GetBaseValue() const {
    return max_value_->GetBaseValue();
}

double AttributeValue::GetCurrentValue() const {
    return max_value_->GetCurrentValue() * relative_value_;
}

double AttributeValue::GetMultiplier() const {
    return max_value_->GetMultiplier();
}

void AttributeValue::Update(float time_elapsed) {
    if (updated_) {
        return;
    }
    updated_ = true;
    UpdateBonuses(time_elapsed, raw_bonuses_);
    UpdateBonuses(time_elapsed, effects_);
}

void AttributeValue::UpdateLevel(int level_change) {
    relative_value_ = 1;
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
    relative_value_ += bonus_value / max_value_->GetCurrentValue();
    relative_value_ *= (1.0 + bonus_multiplier);
}


