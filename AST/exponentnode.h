#ifndef EXPONENTNODE_H
#define EXPONENTNODE_H

#include "../astnode.h"

class ExponentNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    ExponentNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~ExponentNode() override{}

    virtual void deleteChildren() override{
        lhs->deleteChildren();
        delete lhs;
        rhs->deleteChildren();
        delete rhs;
    }

    virtual std::string toString() override{
        return lhs->toString() + '^' + rhs->toString();
    }

    virtual double evaluate() override{
        return pow(lhs->evaluate(), rhs->evaluate());
    }

    virtual AstNode* simplify() override;
};

#endif // EXPONENTNODE_H
