#ifndef NEGATENODE_H
#define NEGATENODE_H

#include "../astnode.h"

class NegateNode : public AstNode{
public:
    AstNode* child;

public:
    NegateNode(AstNode* child){
        this->child = child;
    }

    virtual ~NegateNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return '-' + child->toString();
    }

    virtual double evaluate() override{
        return -child->evaluate();
    }

    virtual AstNode* simplify() override;
};


#endif // NEGATENODE_H
