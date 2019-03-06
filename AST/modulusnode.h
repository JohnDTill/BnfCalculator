#ifndef MODULUSNODE_H
#define MODULUSNODE_H

#include "../astnode.h"

class ModulusNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    ModulusNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~ModulusNode() override{}

    virtual void deleteChildren() override{
        lhs->deleteChildren();
        delete lhs;
        rhs->deleteChildren();
        delete rhs;
    }

    virtual std::string toString() override{
        return lhs->toString() + '%' + rhs->toString();
    }

    virtual double evaluate() override{
        return fmod(lhs->evaluate(), rhs->evaluate());
    }

    virtual AstNode* simplify() override;
};

#endif // MODULUSNODE_H
