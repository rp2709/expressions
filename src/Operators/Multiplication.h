#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Operator.h"

class Multiplication final : public Operator {
public:
    Multiplication() : Operator('*',2,"multiplies left and right") {}
    double apply(double x, double y) override{return x*y;}
};

namespace OperatorInstances {
    const Multiplication multiplication;
}

#endif //MULTIPLICATION_H
