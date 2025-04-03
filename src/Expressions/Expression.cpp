#include "Expression.hpp"

#include <stack>
#include <iostream>

#include "sstream"

// This is the only truly recursive function and has not failed even for comically large expressions of 10'000+ tokens
double Expression::Node::evaluate() const {
    if (isLeaf())
        return value;
    return operand->apply(static_cast<Expression::Node*>(left.get())->evaluate(), static_cast<Expression::Node*>(right.get())->evaluate());
}

std::string Expression::Node::toString()const{
    if(isLeaf())
        return std::to_string(value);
    return std::string() + operand->getSymbol();
}

double Expression::evaluate() const {
    return static_cast<Expression::Node*>(root.get())->evaluate();
}

Expression::Node* Expression::transferRootOf(Expression &&other){
    return static_cast<Expression::Node*>(other.root.release());
}

Expression::Expression(std::istream &expression) {
    double temp;
    char ctmp;
    std::unique_ptr<BinaryTree::Node>* nextNode = &root;
    std::unique_ptr<BinaryTree::Node>* protectedOperator = &root;
    while (not expression.eof()) {
        Node *newNode;
        expression >> ctmp;
        if (ctmp == '(') {
            // This constructor is recursive since it creates a new expression with the content of the parenthesis
            newNode = transferRootOf(Expression(expression));
            protectedOperator = nextNode;
        } else {
            expression.putback(ctmp);
            if (!(expression >> temp))
                throw std::invalid_argument("Invalid expression: direct value could not be parsed");
            newNode = new Node{temp};
        }

        nextNode->reset(newNode);

        expression >> ctmp;
        if (expression.eof() or ctmp == ')') // technically this means that "1)" is valid syntax TODO: stop this
            return;
        Operator *op = Operator::get(ctmp);
        if (op == nullptr)
            throw std::invalid_argument(std::string("Unknown operator : ") + ctmp);

        // from root descent the right most branch of the tree while operator is of greater priority
        nextNode = &root;
        while (
            not(*nextNode)->isLeaf()
            and op->hasGreaterPriorityThan( *(static_cast<Expression::Node*>(nextNode->get())->operand))
            and nextNode != protectedOperator
        )
        {
            nextNode = &(*nextNode)->right;
        }

        nextNode->reset(new Node{op, nextNode->release()});
        nextNode = &(*nextNode)->right;
    }
}
