#ifndef ADDITIONNODE_H
#define ADDITIONNODE_H

#include "binarynode.h"

class AdditionNode : public BinaryNode{
public:
    AdditionNode(AstNode* lhs, AstNode* rhs);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_ADDITION;}
};

#endif // ADDITIONNODE_H
