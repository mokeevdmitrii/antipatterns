//
// Created by dmitry on 4/27/20.
//

#include "Expression.h"

Value::Value(double value) : _current_value(value) {}

double Value::GetCurrentValue() const {
    return _current_value;
}

void Operation::SetLeft(std::shared_ptr<Expression> left) {
    _left = std::move(left);
}

void Operation::SetRight(std::shared_ptr<Expression> right) {
    _right = std::move(right);
}

double Add::GetCurrentValue() const {
    return _left->GetCurrentValue() + _right->GetCurrentValue();
}

double Sub::GetCurrentValue() const {
    return _left->GetCurrentValue() - _right->GetCurrentValue();

}

double Mult::GetCurrentValue() const {
    return _left->GetCurrentValue() * _right->GetCurrentValue();
}

double Div::GetCurrentValue() const {
    return _left->GetCurrentValue() / _right->GetCurrentValue();
}

double Pow::GetCurrentValue() const {
    return pow(_left->GetCurrentValue(), _right->GetCurrentValue());
}

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

std::string LoadString(std::istream &input) {
    std::string line{};
    std::getline(input, line, '"');
    return line;
}
