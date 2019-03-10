#ifndef FACTORIALNODE_H
#define FACTORIALNODE_H

#include "../astnode.h"

class FactorialNode : public AstNode{
private:
    AstNode* child;
    unsigned long long line;

public:
    FactorialNode(AstNode* child, unsigned long long line);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // FACTORIALNODE_H
