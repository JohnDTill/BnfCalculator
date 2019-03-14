#ifndef NATURALLOGNODE_H
#define NATURALLOGNODE_H

#include "unarynode.h"

class NaturalLogNode : public UnaryNode{
public:
    NaturalLogNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};
#endif // NATURALLOGNODE_H
