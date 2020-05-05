//
// Created by dmitry on 4/21/20.
//

#include "Effect.h"


/// ---------------- EFFECT ------------------- ///

Effect::Effect(ATTRIBUTE_ID id, Stats stats, LevelChange level_change) : BaseAttribute(stats, level_change), id_(id) {

}


void Effect::SetAttributeId(ATTRIBUTE_ID id) {
    id_ = id;
}

ATTRIBUTE_ID Effect::GetAttributeid() const {
    return id_;
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
    UpdateBonuses(time_elapsed, raw_bonuses_);
    UpdateBonuses(time_elapsed, effects_);
}

void TimedEffect::SetExpirationTime(float time_to_expire) {
    time_to_expire_ = time_to_expire;
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
    UpdateBonuses(time_elapsed, raw_bonuses_);
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

/// ----------------- CREATE EFFECT -------------- ///

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