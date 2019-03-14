#ifndef BINARYNODE_H
#define BINARYNODE_H

#include "../astnode.h"

class BinaryNode : public AstNode{
public:
    AstNode* lhs;
    AstNode* rhs;

public:
    BinaryNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual void sortChildren() override{}
};

#endif // BINARYNODE_H
