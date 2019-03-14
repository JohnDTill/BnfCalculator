#ifndef TANGENTNODE_H
#define TANGENTNODE_H

#include "unarynode.h"

class TangentNode : public UnaryNode{
public:
    TangentNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // TANGENTNODE_H
