#ifndef ABSOLUTENODE_H
#define ABSOLUTENODE_H

#include "../astnode.h"

class AbsoluteNode : public AstNode{
public:
    AstNode* child;

public:
    AbsoluteNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // ABSOLUTENODE_H
