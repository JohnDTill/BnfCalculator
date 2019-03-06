#ifndef ELITERALNODE_H
#define ELITERALNODE_H

#include "../astnode.h"

class eLiteralNode : public AstNode{
public:
    virtual ~eLiteralNode() override {}

    virtual void deleteChildren() override{}

    virtual std::string toString() override{
        return "e";
    }

    virtual double evaluate() override{
        return 2.71828182845904523536;
    }
};

#endif // ELITERALNODE_H
