#ifndef POWER_H
#define POWER_H

#include "Operator.h"
#include <cmath>

class Power : Operator {
public:
    Power():Operator('^',2,"elevates left at the power of right"){}
    double apply(double x, double y) override{return std::pow(x,y);}
};

namespace OperatorInstances {
    const Power power;
}

#endif //POWER_H
