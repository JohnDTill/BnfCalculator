#ifndef NEGATENODE_H
#define NEGATENODE_H

#include "../astnode.h"

class NegateNode : public AstNode{
public:
    AstNode* child;

public:
    NegateNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};


#endif // NEGATENODE_H
