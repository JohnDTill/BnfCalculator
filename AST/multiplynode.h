#ifndef MULTIPLYNODE_H
#define MULTIPLYNODE_H

#include "../astnode.h"

class MultiplyNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    MultiplyNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // MULTIPLYNODE_H
