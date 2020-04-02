//
// Created by dmitry on 4/2/20.
//

#ifndef ANTIPATTERNS_JSON_H
#define ANTIPATTERNS_JSON_H


#include <istream>
#include <fstream>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace Json {

    class Node : std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            std::string,
            double,
            bool
    > {
    public:
        using variant::variant;

        const auto &AsArray() const {
            return std::get<std::vector<Node>>(*this);
        }

        const auto &AsMap() const {
            return std::get<std::map<std::string, Node>>(*this);
        }

        const auto &AsString() const {
            return std::get<std::string>(*this);
        }

        double AsDouble() const {
            return std::get<double>(*this);
        }

        bool AsBool() const {
            return std::get<bool>(*this);
        }

        static const std::unordered_set<char> POSSIBLE_CHARS_FOR_DOUBLE;
    };

    class Document {
    public:
        explicit Document(Node root);

        const Node &GetRoot() const;

    private:
        Node root;
    };

    Document Load(std::istream &input);

    Document Load(const std::string& file_name);
}
#endif //ANTIPATTERNS_JSON_H
