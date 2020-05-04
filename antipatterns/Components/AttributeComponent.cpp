//

//
// Created by dmitry on 4/2/20.

#include "AttributeComponent.h"

const std::unordered_map<std::string, ATTRIBUTE_ID> AttributeComponent::names_to_id_{
        {"vigor",        ATTRIBUTE_ID::VIGOR},
        {"strength",     ATTRIBUTE_ID::STRENGTH},
        {"dexterity",    ATTRIBUTE_ID::DEXTERITY},
        {"intelligence", ATTRIBUTE_ID::INTELLIGENCE},
        {"faith",        ATTRIBUTE_ID::FAITH},
        {"luck",         ATTRIBUTE_ID::LUCK},
        {"max_hp",       ATTRIBUTE_ID::MAX_HP},
        {"max_mana",     ATTRIBUTE_ID::MAX_MANA},
        {"phys_armor",   ATTRIBUTE_ID::PHYS_ARMOR},
        {"mag_armor",    ATTRIBUTE_ID::MAG_ARMOR},
        {"attack_speed", ATTRIBUTE_ID::ATTACK_SPEED},
        {"base_damage",  ATTRIBUTE_ID::BASE_DAMAGE},
        {"crit_chance",  ATTRIBUTE_ID::CRIT_CHANCE},
        {"curr_hp",      ATTRIBUTE_ID::CURR_HP},
        {"curr_mana",    ATTRIBUTE_ID::CURR_MANA}
};

const std::unordered_map<ATTRIBUTE_ID, std::vector<ATTRIBUTE_ID>> AttributeComponent::dependence_{
        {ATTRIBUTE_ID::MAX_HP,       {ATTRIBUTE_ID::VIGOR}},
        {ATTRIBUTE_ID::MAX_MANA,     {ATTRIBUTE_ID::INTELLIGENCE, ATTRIBUTE_ID::FAITH}},
        {ATTRIBUTE_ID::PHYS_ARMOR,   {ATTRIBUTE_ID::VIGOR,        ATTRIBUTE_ID::STRENGTH, ATTRIBUTE_ID::DEXTERITY}},
        {ATTRIBUTE_ID::MAG_ARMOR,    {ATTRIBUTE_ID::FAITH,        ATTRIBUTE_ID::VIGOR,    ATTRIBUTE_ID::INTELLIGENCE}},
        {ATTRIBUTE_ID::ATTACK_SPEED, {ATTRIBUTE_ID::DEXTERITY,    ATTRIBUTE_ID::STRENGTH, ATTRIBUTE_ID::INTELLIGENCE}},
        {ATTRIBUTE_ID::BASE_DAMAGE,  {ATTRIBUTE_ID::STRENGTH,     ATTRIBUTE_ID::DEXTERITY}},
        {ATTRIBUTE_ID::CRIT_CHANCE,  {ATTRIBUTE_ID::LUCK,         ATTRIBUTE_ID::DEXTERITY}},
        {ATTRIBUTE_ID::CURR_HP,      {ATTRIBUTE_ID::MAX_HP}},
        {ATTRIBUTE_ID::CURR_MANA,    {ATTRIBUTE_ID::MAX_MANA}}
};

const std::unordered_map<ATTRIBUTE_ID, std::pair<double, double>> AttributeComponent::id_boundaries_{
        {ATTRIBUTE_ID::VIGOR,        {0,           D_INFINITY}},
        {ATTRIBUTE_ID::STRENGTH,     {0,           D_INFINITY}},
        {ATTRIBUTE_ID::DEXTERITY,    {0,           D_INFINITY}},
        {ATTRIBUTE_ID::INTELLIGENCE, {0,           D_INFINITY}},
        {ATTRIBUTE_ID::FAITH,        {0,           D_INFINITY}},
        {ATTRIBUTE_ID::LUCK,         {0,           D_INFINITY}},
        {ATTRIBUTE_ID::MAX_HP,       {1,           D_INFINITY}},
        {ATTRIBUTE_ID::MAX_MANA,     {1,           D_INFINITY}},
        {ATTRIBUTE_ID::PHYS_ARMOR,   {-D_INFINITY, 1}},
        {ATTRIBUTE_ID::MAG_ARMOR,    {-D_INFINITY, 1}},
        {ATTRIBUTE_ID::ATTACK_SPEED, {0,           D_INFINITY}},
        {ATTRIBUTE_ID::BASE_DAMAGE,  {0,           D_INFINITY}},
        {ATTRIBUTE_ID::CRIT_CHANCE,  {0,           1}},
        {ATTRIBUTE_ID::CURR_HP,      {0,           1}},
        {ATTRIBUTE_ID::CURR_MANA,    {0,           1}}
};

const std::unordered_map<ATTRIBUTE_ID, std::function<double(
        const std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>> &)>> AttributeComponent::id_to_functions_{
        {ATTRIBUTE_ID::MAX_HP,       stats_formula::MaxHPFunction},
        {ATTRIBUTE_ID::MAX_MANA,     stats_formula::MaxManaFunction},
        {ATTRIBUTE_ID::PHYS_ARMOR,   stats_formula::PhysArmorFunction},
        {ATTRIBUTE_ID::MAG_ARMOR,    stats_formula::MagArmorFunction},
        {ATTRIBUTE_ID::ATTACK_SPEED, stats_formula::AttackSpeedFunction},
        {ATTRIBUTE_ID::BASE_DAMAGE,  stats_formula::BaseDamageFunction},
        {ATTRIBUTE_ID::CRIT_CHANCE,  stats_formula::CritChanceFunction},
};

AttributeComponent::AttributeComponent(const std::map<std::string, Json::Node> &settings) {
    attributes_.resize(names_to_id_.size());
    LoadFromMap(settings);
    this->Update(0);
}

AttributeComponent::AttributeComponent(const AttributeComponent &other) {
    *this = other;
}

AttributeComponent &AttributeComponent::operator=(const AttributeComponent &other) {
    if (&other == this) {
        return *this;
    }
    level_ = other.level_;
    attributes_ = std::vector<std::shared_ptr<BaseAttribute>>();
    for (const auto &attribute : other.attributes_) {
        attributes_.push_back(attribute->Clone());
    }
    ResetAttributesDependence();
    this->Update(0);
    return *this;
}


void AttributeComponent::Update(float time_elapsed) {
    for (auto &attribute : attributes_) {
        attribute->Update(time_elapsed);
    }
    CheckBoundaries();
}


void AttributeComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    LoadBaseAttributes(settings.at("base_attributes").AsMap());
    LoadDependantAttributes(settings.at("dependant_attributes").AsMap());
    LoadChangingAttributes(settings.at("changing_attributes").AsMap());
}

double AttributeComponent::GetAttributeValue(ATTRIBUTE_ID id) {
    return attributes_.at(static_cast<size_t>(id))->GetCurrentValue();
}


int AttributeComponent::GetLevel() const {
    return level_;
}


void AttributeComponent::ResetAttributesDependence() {
    for (size_t curr_index = 0; curr_index < attributes_.size(); ++curr_index) {
        auto curr_id = static_cast<ATTRIBUTE_ID>(curr_index);
        if (dependence_.count(curr_id) != 0) {
            for (ATTRIBUTE_ID id : dependence_.at(curr_id)) {
                attributes_[curr_index]->AddDependantAttribute(id, attributes_.at(static_cast<size_t>(id)));
            }
        }
    }
}

void AttributeComponent::CheckBoundaries() {
    for (size_t i = 0; i < attributes_.size(); ++i) {
        auto curr_id = static_cast<ATTRIBUTE_ID>(i);
        if (attributes_[i]->GetCurrentValue() < id_boundaries_.at(curr_id).first) {
            attributes_[i]->SetCurrentValue(id_boundaries_.at(curr_id).first);
        } else if (attributes_[i]->GetCurrentValue() > id_boundaries_.at(curr_id).second) {
            attributes_[i]->SetCurrentValue(id_boundaries_.at(curr_id).second);
        }
    }
}


void AttributeComponent::LoadBaseAttributes(const std::map<std::string, Json::Node> &settings) {
    Stats temp_stats{};
    LevelChange temp_level_change{};
    for (const auto&[attr_name, attr_settings] : settings) {
        GetBaseStats(temp_stats, temp_level_change, attr_settings.AsMap());
        auto curr_id = names_to_id_.at(attr_name);
        auto curr_index = static_cast<size_t>(curr_id);
        attributes_.at(curr_index) = std::make_shared<BaseAttribute>(temp_stats, temp_level_change);
    }
}

void AttributeComponent::LoadDependantAttributes(const std::map<std::string, Json::Node> &settings) {
    Stats temp_stats{};
    LevelChange level_change{};
    for (const auto&[attr_name, attr_settings] : settings) {
        GetBaseStats(temp_stats, level_change, attr_settings.AsMap());
        auto curr_id = names_to_id_.at(attr_name);
        auto curr_index = static_cast<size_t>(curr_id);
        std::shared_ptr<Attribute> curr_attr = std::make_shared<Attribute>(temp_stats, level_change,
                                                                           id_to_functions_.at(
                                                                                   static_cast<ATTRIBUTE_ID>(curr_index)));
        for (const ATTRIBUTE_ID &dependent_id : dependence_.at(curr_id)) {
            curr_attr->AddDependantAttribute(dependent_id, attributes_.at(static_cast<int>(dependent_id)));
        }
        attributes_.at(curr_index) = std::move(curr_attr);
    }
}

void AttributeComponent::LoadChangingAttributes(const std::map<std::string, Json::Node> &settings) {
    for (const auto&[attr_name, attr_settings] : settings) {
        auto curr_id = names_to_id_.at(attr_name);
        auto curr_index = static_cast<size_t>(curr_id);
        //вектор гарантированно содержит всего 1 элемент!
        auto max_value_index = static_cast<size_t>(dependence_.at(curr_id).front());
        attributes_.at(curr_index) = std::make_shared<AttributeValue>(attributes_.at(max_value_index));
    }
}

void AttributeComponent::GetBaseStats(Stats &stats, LevelChange &level_change,
                                      const std::map<std::string, Json::Node> &settings) {
    stats.base_value = settings.at("stats").AsMap().at("base_value").AsDouble();
    stats.multiplier = settings.at("stats").AsMap().at("multiplier").AsDouble();
    level_change.delta_value = settings.at("level_change").AsMap().at("delta_value").AsDouble();
    level_change.multiplier = settings.at("level_change").AsMap().at("multiplier").AsDouble();
}







