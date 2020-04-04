//
// Created by dmitry on 4/2/20.
//

#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(const std::map<std::string, Json::Node>& settings) {
    LoadFromMap(settings);
}

void AttributeComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    _level = static_cast<int>(settings.at("level").AsDouble());
    _health = static_cast<int>(settings.at("health").AsDouble());
    _health_per_level = static_cast<int>(settings.at("health_per_level").AsDouble());
}

int AttributeComponent::GetLevel() {
    return _level;
}



