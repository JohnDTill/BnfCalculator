#ifndef FACTORIALNODE_H
#define FACTORIALNODE_H

#include "unarynode.h"

class FactorialNode : public UnaryNode{
private:
    unsigned long long line;

public:
    FactorialNode(AstNode* child, unsigned long long line);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_FACTORIAL;}
};

#endif // FACTORIALNODE_H
