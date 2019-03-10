#ifndef PiLiteralNode_H
#define PiLiteralNode_H

#include "../astnode.h"

class PiLiteralNode : public AstNode{
public:
    virtual void deleteChildren() override{}
    virtual std::string toString() override;
    virtual double evaluate() override;
};

#endif
