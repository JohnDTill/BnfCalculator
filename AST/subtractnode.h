#ifndef SUBTRACTNODE_H
#define SUBTRACTNODE_H

#include "../astnode.h"

class SubtractNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    SubtractNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // SUBTRACTNODE_H
