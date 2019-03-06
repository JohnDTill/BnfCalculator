#ifndef DIVIDENODE_H
#define DIVIDENODE_H

#include "../astnode.h"

class DivideNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    DivideNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~DivideNode() override{}

    virtual void deleteChildren() override{
        lhs->deleteChildren();
        delete lhs;
        rhs->deleteChildren();
        delete rhs;
    }

    virtual std::string toString() override{
        return lhs->toString() + " / " + rhs->toString();
    }

    virtual double evaluate() override{
        return lhs->evaluate() / rhs->evaluate();
    }

    virtual AstNode* simplify() override;
};

#endif // DIVIDENODE_H
