#ifndef COSINENODE_H
#define COSINENODE_H

#include "../astnode.h"

class CosineNode : public AstNode{
private:
    AstNode* child;

public:
    CosineNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // COSINENODE_H
