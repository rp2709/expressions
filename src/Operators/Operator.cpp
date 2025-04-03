#include "Operator.h"

bool Operator::hasGreaterPriorityThan(const Operator &other) const {
    return priority > other.priority;
}

std::ostream &operator<<(std::ostream &os, const Operator& op) {
    return os << "Symbol: " << op.symbol
           << " Priority: " << op.priority
           << "(" << op.description << ")";
}

Operator * Operator::get(char symbol) {
    if (symbolToOperator.contains(symbol))
        return symbolToOperator[symbol];
    return nullptr;
}

std::vector<Operator*> Operator::getAll() {
    std::vector<Operator*> result;
    result.reserve(symbolToOperator.size());
    for (auto[key,op] : symbolToOperator) {
        result.push_back(op);
    }
    return result;
}

Operator::Operator(const char symbol, const int priority, std::string description): symbol(symbol), priority(priority),description(std::move(description)) {
    symbolToOperator.emplace(symbol, this);
}

Operator::~Operator() {
    symbolToOperator.erase(symbol);
}
