#ifndef DIVIDENODE_H
#define DIVIDENODE_H

#include "../astnode.h"

class DivideNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    DivideNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // DIVIDENODE_H
