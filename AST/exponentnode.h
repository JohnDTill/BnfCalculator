#ifndef EXPONENTNODE_H
#define EXPONENTNODE_H

#include "binarynode.h"

class ExponentNode : public BinaryNode{
public:
    ExponentNode(AstNode* lhs, AstNode* rhs);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_EXPONENTIATION;}
};

#endif // EXPONENTNODE_H
