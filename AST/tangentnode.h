#ifndef TANGENTNODE_H
#define TANGENTNODE_H

#include "../astnode.h"

class TangentNode : public AstNode{
private:
    AstNode* child;

public:
    TangentNode(AstNode* child){
        this->child = child;
    }

    virtual ~TangentNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return "tan(" + child->toString() + ')';
    }

    virtual double evaluate() override{
        return tan(child->evaluate());
    }

    virtual AstNode* simplify() override;
};

#endif // TANGENTNODE_H
