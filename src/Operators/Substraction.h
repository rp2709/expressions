#ifndef SUBSTRACTION_H
#define SUBSTRACTION_H

#include "Operator.h"

class Substraction final : public Operator {
public:
    Substraction() : Operator('-',1,"substracts right from left") {}
    double apply(double x, double y) override{return x-y;}
};

namespace OperatorInstances {
    const Substraction substraction;
}

#endif //SUBSTRACTION_H
