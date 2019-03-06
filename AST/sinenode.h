#ifndef SINENODE_H
#define SINENODE_H

#include "../astnode.h"

class SineNode : public AstNode{
private:
    AstNode* child;

public:
    SineNode(AstNode* child){
        this->child = child;
    }

    virtual ~SineNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return "sin(" + child->toString() + ')';
    }

    virtual double evaluate() override{
        return sin(child->evaluate());
    }

    virtual AstNode* simplify() override;
};

#endif // SINENODE_H
