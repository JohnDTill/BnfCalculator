#ifndef NATURALLOGNODE_H
#define NATURALLOGNODE_H

#include "../astnode.h"

class NaturalLogNode : public AstNode{
private:
    AstNode* child;

public:
    NaturalLogNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};
#endif // NATURALLOGNODE_H
