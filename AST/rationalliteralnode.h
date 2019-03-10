#ifndef RATIONALLITERALNODE_H
#define RATIONALLITERALNODE_H

#include "../astnode.h"

class RationalLiteralNode : public AstNode{
public:
    rational val;

public:
    RationalLiteralNode(rational val);
    virtual void deleteChildren() override{}
    virtual std::string toString() override;
    virtual double evaluate() override;
};

#endif // RATIONALLITERALNODE_H
