//
// Created by dmitry on 4/21/20.
//

#ifndef ANTIPATTERNS_PARAMETER_H
#define ANTIPATTERNS_PARAMETER_H


class Parameter {
public:
    explicit Parameter(double value) : _value(value) {

    }

    double GetValue() const {
        return _value;
    }

    void SetValue(double value) {
        _value = value;
    }

private:
    double _value;
};


#endif //ANTIPATTERNS_PARAMETER_H
