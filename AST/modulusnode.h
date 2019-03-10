#ifndef MODULUSNODE_H
#define MODULUSNODE_H

#include "../astnode.h"

class ModulusNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    ModulusNode(AstNode* lhs, AstNode* rhs);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // MODULUSNODE_H
