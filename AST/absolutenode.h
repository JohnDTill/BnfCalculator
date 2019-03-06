#ifndef ABSOLUTENODE_H
#define ABSOLUTENODE_H

#include "../astnode.h"

class AbsoluteNode : public AstNode{
public:
    AstNode* child;

public:
    AbsoluteNode(AstNode* child){
        this->child = child;
    }

    virtual ~AbsoluteNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return '|' + child->toString() + '|';
    }

    virtual double evaluate() override{
        return abs(child->evaluate());
    }

    virtual AstNode* simplify() override;
};

#endif // ABSOLUTENODE_H
