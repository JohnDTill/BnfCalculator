#ifndef LOGNODE_H
#define LOGNODE_H

#include "../astnode.h"

class LogNode : public AstNode{
private:
    AstNode* child;

public:
    LogNode(AstNode* child){
        this->child = child;
    }

    virtual ~LogNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return "log(" + child->toString() + ')';
    }

    virtual double evaluate() override{
        return log10(child->evaluate());
    }
};

#endif // LOGNODE_H
