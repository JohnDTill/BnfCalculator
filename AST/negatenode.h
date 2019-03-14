#ifndef NEGATENODE_H
#define NEGATENODE_H

#include "unarynode.h"

class NegateNode : public UnaryNode{
public:
    NegateNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NEGATION;}
};


#endif // NEGATENODE_H
