//
// Created by dmitry on 4/2/20.
//

#include "AttributeComponent.h"

const std::unordered_map<std::string, ATTRIBUTE_ID> AttributeComponent::_names_to_id = {};

AttributeComponent::AttributeComponent(const std::map<std::string, Json::Node> &settings) {
    LoadFromMap(settings);
}

void AttributeComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    _level = static_cast<int>(settings.at("level").AsDouble());
    _health = static_cast<int>(settings.at("health").AsDouble());
    _health_per_level = static_cast<int>(settings.at("health_per_level").AsDouble());
}

std::shared_ptr<BaseAttribute> AttributeComponent::GetAttribute(ATTRIBUTE_ID id) {
    return _attributes.at(id);
}


int AttributeComponent::GetLevel() const {
    return _level;
}

void AttributeComponent::LoadBaseAttributes(const std::map<std::string, Json::Node> &settings) {
    Stats _temp_stats{};
    LevelChange _level_change{};
    for (const auto&[name, map] : settings) {

    }

}

std::shared_ptr<Expression> AttributeComponent::ParseExpression(std::string expression) {
    std::istringstream input(expression);
    return LoadNode(input);
}

std::shared_ptr<Expression> AttributeComponent::LoadNode(std::istream &input) {
    char c;
    input >> c;
    while (c == ' ') {
        input >> c;
    }
    if (isalpha(c)) {
        std::string id_string = LoadString(input);
        ATTRIBUTE_ID _id = _names_to_id.at(id_string);
        std::shared_ptr<Expression> result = _attributes.at(_id);
        return result;
    } else if (isdigit(c)) {
        std::shared_ptr<Expression> result = std::make_shared<Value>(LoadDouble(input));
        return result;
    } else if (MATH_OPERATORS::SUPPORTED_OPERATORS.count(c) != 0) {
        std::shared_ptr<Operation> result = CreateOperation(c);
        result->SetLeft(LoadNode(input));
        result->SetRight(LoadNode(input));
        return result;
    }
    throw (std::runtime_error("Wrong attribute expression parsing"));
}






