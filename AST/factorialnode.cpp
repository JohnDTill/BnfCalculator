#include "factorialnode.h"

#include "rationalliteralnode.h"

FactorialNode::FactorialNode(AstNode* child, unsigned long long line)
    : UnaryNode(child){
    this->line = line;
}

std::string FactorialNode::toString(){
    return child->toString(getPrecedence()) + '!';
}

double FactorialNode::evaluate(){
    double val = child->evaluate();
    int rounded = static_cast<int>(val);
    double decimal_part = val - rounded;
    if(decimal_part > 1e-9 && 1-decimal_part > 1e-9)
        error("Factorial has non-integer argument");

    if(rounded < 0) error("Factorial has negative argument");

    int factorial = 1;
    for(int i = 2; i <= rounded; factorial *= i++);

    return factorial;
}

AstNode* FactorialNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(!n->val.denominator.isOne())
            error("Factorial has non-integer argument");
        if(n->val.is_negative) error("Factorial has negative argument");

        big_uint factorial = 1;
        for(big_uint i = 2; i < n->val.numerator; factorial *= i++);
        n->val.numerator = factorial;

        return n;
    }

    return this;
}

NodeType FactorialNode::getType(){
    return FACTORIAL;
}
