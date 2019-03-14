#ifndef FLATMULTIPLYNODE_H
#define FLATMULTIPLYNODE_H

#include "narynode.h"

class FlatMultiplyNode : public NAryNode{
public:
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_MULTIPLICATION;}
};

#endif // FLATMULTIPLYNODE_H
