#ifndef MULTIPLYNODE_H
#define MULTIPLYNODE_H

#include "../astnode.h"

class MultiplyNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    MultiplyNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~MultiplyNode() override{}

    virtual void deleteChildren() override{
        lhs->deleteChildren();
        delete lhs;
        rhs->deleteChildren();
        delete rhs;
    }

    virtual std::string toString() override{
        return lhs->toString() + '*' + rhs->toString();
    }

    virtual double evaluate() override{
        return lhs->evaluate() * rhs->evaluate();
    }

    virtual AstNode* simplify() override;
};

#endif // MULTIPLYNODE_H
