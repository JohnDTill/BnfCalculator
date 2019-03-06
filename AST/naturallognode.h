#ifndef NATURALLOGNODE_H
#define NATURALLOGNODE_H

#include "../astnode.h"

class NaturalLogNode : public AstNode{
private:
    AstNode* child;

public:
    NaturalLogNode(AstNode* child){
        this->child = child;
    }

    virtual ~NaturalLogNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return "ln(" + child->toString() + ')';
    }

    virtual double evaluate() override{
        return log(child->evaluate());
    }
};
#endif // NATURALLOGNODE_H
