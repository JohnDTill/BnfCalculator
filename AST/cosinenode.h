#ifndef COSINENODE_H
#define COSINENODE_H

#include "../astnode.h"

class CosineNode : public AstNode{
private:
    AstNode* child;

public:
    CosineNode(AstNode* child){
        this->child = child;
    }

    virtual ~CosineNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return "cos(" + child->toString() + ')';
    }

    virtual double evaluate() override{
        return cos(child->evaluate());
    }

    virtual AstNode* simplify() override;
};

#endif // COSINENODE_H
