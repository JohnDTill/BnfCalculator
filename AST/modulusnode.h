#ifndef MODULUSNODE_H
#define MODULUSNODE_H

#include "binarynode.h"

class ModulusNode : public BinaryNode{
public:
    ModulusNode(AstNode* lhs, AstNode* rhs);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_MULTIPLICATION;}
};

#endif // MODULUSNODE_H
