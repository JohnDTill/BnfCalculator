#ifndef DIVIDENODE_H
#define DIVIDENODE_H

#include "binarynode.h"

class DivideNode : public BinaryNode{
public:
    DivideNode(AstNode* lhs, AstNode* rhs);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_MULTIPLICATION;}
};

#endif // DIVIDENODE_H
