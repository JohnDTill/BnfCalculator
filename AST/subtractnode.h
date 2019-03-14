#ifndef SUBTRACTNODE_H
#define SUBTRACTNODE_H

#include "binarynode.h"

class SubtractNode : public BinaryNode{
public:
    SubtractNode(AstNode* lhs, AstNode* rhs);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_ADDITION;}
};

#endif // SUBTRACTNODE_H
