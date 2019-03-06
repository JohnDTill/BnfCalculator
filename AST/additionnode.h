#ifndef ADDITIONNODE_H
#define ADDITIONNODE_H

#include "../astnode.h"

class AdditionNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    AdditionNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~AdditionNode() override{}

    virtual void deleteChildren() override{
        lhs->deleteChildren();
        delete lhs;
        rhs->deleteChildren();
        delete rhs;
    }

    virtual std::string toString() override{
        return lhs->toString() + " + " + rhs->toString();
    }

    virtual double evaluate() override{
        return lhs->evaluate() + rhs->evaluate();
    }

    virtual AstNode* simplify() override;
};

#endif // ADDITIONNODE_H
