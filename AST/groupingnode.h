#ifndef GROUPINGNODE_H
#define GROUPINGNODE_H

#include "../astnode.h"

class GroupingNode : public AstNode{
private:
    AstNode* child;

public:
    GroupingNode(AstNode* child){
        this->child = child;
    }

    virtual ~GroupingNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return '(' + child->toString() + ')';
    }

    virtual double evaluate() override{
        return child->evaluate();
    }

    virtual AstNode* simplify() override;
};

#endif // GROUPINGNODE_H
