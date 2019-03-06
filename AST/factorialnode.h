#ifndef FACTORIALNODE_H
#define FACTORIALNODE_H

#include "../astnode.h"

class FactorialNode : public AstNode{
private:
    AstNode* child;
    unsigned long long line;

public:
    FactorialNode(AstNode* child, unsigned long long line){
        this->child = child;
        this->line = line;
    }

    virtual ~FactorialNode() override{}

    virtual void deleteChildren() override{
        child->deleteChildren();
        delete child;
    }

    virtual std::string toString() override{
        return child->toString() + '!';
    }

    virtual double evaluate() override;

    virtual AstNode* simplify() override;
};

#endif // FACTORIALNODE_H
