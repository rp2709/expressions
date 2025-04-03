#ifndef ADDITION_H
#define ADDITION_H

#include "Operator.h"

class Addition final : public Operator {
public:
    Addition() : Operator('+',1,"adds left and right") {}
    double apply(double x, double y) override{return x+y;}
};

namespace OperatorInstances {
    const Addition addition;
}

#endif //ADDITION_H
