#ifndef UNARYNODE_H
#define UNARYNODE_H

#include "../astnode.h"

class UnaryNode : public AstNode{
public:
    AstNode* child;

public:
    UnaryNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual void sortChildren() override{}
};

#endif // UNARYNODE_H
