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

    Value(double value) : _current_value(value) {}

    double GetCurrentValue() const override {
        return _current_value;
    }

protected:
    double _current_value{};
};

class Operation : public Expression {
public:
    void SetLeft(std::shared_ptr<Expression> left) {
        _left = std::move(left);
    }

    void SetRight(std::shared_ptr<Expression> right) {
        _right = std::move(right);
    }
protected:
    std::shared_ptr<Expression> _left{nullptr};
    std::shared_ptr<Expression> _right{nullptr};
};

class Add : public Operation {
public:
    double GetCurrentValue() const override {
        return _left->GetCurrentValue() + _right->GetCurrentValue();
    }
};

class Sub : public Operation {
    double GetCurrentValue() const override {
        return _left->GetCurrentValue() - _right->GetCurrentValue();

    }
};

class Mult : public Operation {
    double GetCurrentValue() const override {
        return _left->GetCurrentValue() * _right->GetCurrentValue();
    }
};

class Div : public Operation {
    double GetCurrentValue() const override {
        return _left->GetCurrentValue() / _right->GetCurrentValue();
    }
};

class Pow : public Operation {
    double GetCurrentValue() const override {
        return pow(_left->GetCurrentValue(), _right->GetCurrentValue());
    }
};

std::shared_ptr<Operation> CreateOperation(char symbol) {
    if (symbol == '+') {
        return std::make_shared<Add>();
    } else if (symbol == '-') {
        return std::make_shared<Sub>();
    } else if (symbol == '*') {
        return std::make_shared<Mult>();
    } else if (symbol == '/') {
        return std::make_shared<Div>();
    } else if (symbol == '^') {
        return std::make_shared<Pow>();
    }
    throw std::runtime_error("Unknown math symbol in expression");
}

//parsing double
double LoadDouble(std::istream &input) {
    double result = 0;
    bool flag = false;
    if (input.peek() == '-') {
        flag = true;
        input.get();
    }
    while (isdigit(input.peek())) {
        result *= 10;
        result += input.get() - '0';
    }
    if (input.peek() == '.') {
        long double decimal_part = 0;
        long double count = 1;
        input.get();
        while (isdigit(input.peek())) {
            decimal_part *= 10;
            count *= 10;
            decimal_part += input.get() - '0';
        }
        result += static_cast<double>(decimal_part / count);
    }
    if (flag) {
        result *= -1;
    }
    return result;
}

std::string LoadString(std::istream& input) {
    std::string line{};
    std::getline(input, line, '"');
    return line;
}








#endif //ANTIPATTERNS_EXPRESSION_H
