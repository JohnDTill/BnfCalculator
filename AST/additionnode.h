#ifndef ADDITIONNODE_H
#define ADDITIONNODE_H

#include "../astnode.h"

class AdditionNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    AdditionNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // ADDITIONNODE_H
