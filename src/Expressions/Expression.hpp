#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <istream>
#include "../Operators/Operator.h"
#include "../TreeVisualizer/BinaryTree.hpp"

class Expression : public BinaryTree{
  struct Node : public BinaryTree::Node{
            union {
                double value;
                Operator* operand;
            };
            Node(double value):value(value){}
            Node(Operator* operand, BinaryTree::Node* left):operand(operand){this->left.reset(left);}
            double evaluate()const;
            std::string toString()const override;
        };
  static Node* transferRootOf(Expression&& other);
public:
  Expression(std::istream& stringExpression);
  double evaluate()const;
};

#endif //CALCULATOR_H
