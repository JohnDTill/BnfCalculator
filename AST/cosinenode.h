#ifndef COSINENODE_H
#define COSINENODE_H

#include "unarynode.h"

class CosineNode : public UnaryNode{
public:
    CosineNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // COSINENODE_H
