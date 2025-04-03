#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <ostream>
#include <unordered_map>
#include <vector>

/*
 * Base class of all operators
 * Since they are all supposed to be singletons, Operator provides a
 * static method to retrieve the operator corresponding to a symbol
 */
class Operator {
    const char symbol;
    const int priority;
    const std::string description;

    inline static std::unordered_map<char, Operator*> symbolToOperator;
protected:
    Operator(char symbol, int priority, std::string description);
public:
    virtual ~Operator();
    virtual double apply(double x, double y) = 0;
    bool hasGreaterPriorityThan(const Operator& other) const;
    friend std::ostream& operator << (std::ostream& os, const Operator& op);
    char getSymbol()const{return symbol;}

    static Operator* get(char symbol);
    static std::vector<Operator*> getAll();
};


#endif //OPERATOR_H
