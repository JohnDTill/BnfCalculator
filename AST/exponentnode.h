#ifndef EXPONENTNODE_H
#define EXPONENTNODE_H

#include "../astnode.h"

class ExponentNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    ExponentNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // EXPONENTNODE_H
