#ifndef SUBTRACTNODE_H
#define SUBTRACTNODE_H

#include "../astnode.h"

class SubtractNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    SubtractNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~SubtractNode() override{}

    virtual void deleteChildren() override{
        lhs->deleteChildren();
        delete lhs;
        rhs->deleteChildren();
        delete rhs;
    }

    virtual std::string toString() override{
        return lhs->toString() + " - " + rhs->toString();
    }

    virtual double evaluate() override{
        return lhs->evaluate() - rhs->evaluate();
    }

    virtual AstNode* simplify() override;
};

#endif // SUBTRACTNODE_H
