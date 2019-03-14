#ifndef ABSOLUTENODE_H
#define ABSOLUTENODE_H

#include "unarynode.h"

class AbsoluteNode : public UnaryNode{
public:
    AbsoluteNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // ABSOLUTENODE_H
