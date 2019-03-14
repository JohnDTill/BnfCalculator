#ifndef SINENODE_H
#define SINENODE_H

#include "unarynode.h"

class SineNode : public UnaryNode{
public:
    SineNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // SINENODE_H
