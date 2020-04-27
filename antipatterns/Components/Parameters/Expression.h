//
// Created by dmitry on 4/27/20.
//

#ifndef ANTIPATTERNS_EXPRESSION_H
#define ANTIPATTERNS_EXPRESSION_H

#include <list>
#include <set>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include "../../Resources/Json.h"

namespace MATH_OPERATORS {
    static const std::set<char> SUPPORTED_OPERATORS{'+', '-', '*', '/', '^'};
}

class Expression {
public:
    Expression() = default;
    virtual ~Expression() = default;

    virtual double GetCurrentValue() const = 0;
};

class Value : public Expression {
public:
    Value() = default;

    Value(double value);

    double GetCurrentValue() const override;

protected:
    double _current_value{};
};

class Operation : public Expression {
public:
    void SetLeft(std::shared_ptr<Expression> left);

    void SetRight(std::shared_ptr<Expression> right);
protected:
    std::shared_ptr<Expression> _left{nullptr};
    std::shared_ptr<Expression> _right{nullptr};
};

class Add : public Operation {
public:
    double GetCurrentValue() const override;
};

class Sub : public Operation {
    double GetCurrentValue() const override;
};

class Mult : public Operation {
    double GetCurrentValue() const override;
};

class Div : public Operation {
    double GetCurrentValue() const override;
};

class Pow : public Operation {
    double GetCurrentValue() const override;
};

std::shared_ptr<Operation> CreateOperation(char symbol);

//parsing double
double LoadDouble(std::istream &input);

std::string LoadString(std::istream& input);








#endif //ANTIPATTERNS_EXPRESSION_H
