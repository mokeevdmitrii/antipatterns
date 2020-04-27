//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTECOMPONENT_H
#define ANTIPATTERNS_ATTRIBUTECOMPONENT_H

#include "GraphicsComponent.h"
#include "Parameters/Attribute.h"

class AttributeComponent {
public:
    explicit AttributeComponent(const std::map<std::string, Json::Node>& settings);
    AttributeComponent(const AttributeComponent& other) = default;
    AttributeComponent& operator = (const AttributeComponent& other) = default;
    ~AttributeComponent() = default;

    void LoadFromMap(const std::map<std::string, Json::Node>& settings);

    std::shared_ptr<BaseAttribute> GetAttribute(ATTRIBUTE_ID id);
    int GetLevel() const;
private:
    void LoadBaseAttributes(const std::map<std::string, Json::Node>& settings);
    void LoadDerivedAttributes(const std::map<std::string, Json::Node>& settings);
    void LoadChangingAttributes(const std::map<std::string, Json::Node>& settings);

    std::shared_ptr<Expression> ParseExpression(std::string expression);
    std::shared_ptr<Expression> LoadNode(std::istream& input);

    std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>> _attributes;
    static std::unordered_map<std::string, ATTRIBUTE_ID> _names_to_id;
    int _level{1};
    int _health;
    int _health_per_level;
};


#endif //ANTIPATTERNS_ATTRIBUTECOMPONENT_H
