#ifndef MULTIPLYNODE_H
#define MULTIPLYNODE_H

#include "binarynode.h"
class MultiplyNode : public BinaryNode{
public:
    MultiplyNode(AstNode* lhs, AstNode* rhs);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_MULTIPLICATION;}
};

#endif // MULTIPLYNODE_H
