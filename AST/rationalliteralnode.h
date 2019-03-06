#ifndef RATIONALLITERALNODE_H
#define RATIONALLITERALNODE_H

#include "../astnode.h"

class RationalLiteralNode : public AstNode{
public:
    rational val;

public:
    RationalLiteralNode(rational val){
        this->val = val;
    }

    virtual void deleteChildren() override{}

    virtual std::string toString() override{
        return val.toString();
    }

    virtual double evaluate() override{
        double magnitude = std::atoi(val.numerator.toString().data()) / static_cast<double>(std::atoi(val.denominator.toString().data()));
        return val.is_negative ? -magnitude : magnitude;
    }
};

#endif // RATIONALLITERALNODE_H
