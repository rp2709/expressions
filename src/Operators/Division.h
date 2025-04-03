#ifndef DIVISION_H
#define DIVISION_H

#include "Operator.h"

class Division final : public Operator {
public:
    Division() : Operator('/',2,"divides left by right") {}
    double apply(double x, double y) override{return x/y;}
};

namespace OperatorInstances {
    const Division division;
}

#endif //DIVISION_H
