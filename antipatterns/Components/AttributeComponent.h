//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_ATTRIBUTECOMPONENT_H
#define ANTIPATTERNS_ATTRIBUTECOMPONENT_H

#include "GraphicsComponent.h"
#include "Parameters/AttributeFormulas.h"
#include "../Resources/Constants.h"

class AttributeComponent {
public:
    explicit AttributeComponent(const std::map<std::string, Json::Node> &settings);

    AttributeComponent(const AttributeComponent &other);

    AttributeComponent &operator=(const AttributeComponent &other);

    ~AttributeComponent() = default;

    void Update(float time_elapsed);

    void LoadFromMap(const std::map<std::string, Json::Node> &settings);

    double GetAttributeValue(ATTRIBUTE_ID id);

    int GetLevel() const;
private:
    void ResetAttributesDependence();

    void CheckBoundaries();

    void LoadBaseAttributes(const std::map<std::string, Json::Node> &settings);

    void LoadDependantAttributes(const std::map<std::string, Json::Node> &settings);

    void LoadChangingAttributes(const std::map<std::string, Json::Node> &settings);

    void GetBaseStats(Stats& stats, LevelChange& level_change, const std::map<std::string, Json::Node>& settings);

    std::vector<std::shared_ptr<BaseAttribute>> _attributes;
    int _level{1};

    static const std::unordered_map<std::string, ATTRIBUTE_ID> _names_to_id;

    static const std::unordered_map<ATTRIBUTE_ID, std::vector<ATTRIBUTE_ID>> _dependence;

    static const std::unordered_map<ATTRIBUTE_ID, std::pair<double, double>> _id_boundaries;
    using BaseStats = std::unordered_map<ATTRIBUTE_ID, std::shared_ptr<BaseAttribute>>;
    using StatsFunc = std::function<double(const BaseStats &)>;


    static const std::unordered_map<ATTRIBUTE_ID, StatsFunc> _id_to_functions;
};


#endif //ANTIPATTERNS_ATTRIBUTECOMPONENT_H
