#ifndef PiLiteralNode_H
#define PiLiteralNode_H

#include "../astnode.h"

class PiLiteralNode : public AstNode{
public:
    virtual void deleteChildren() override{}

    virtual std::string toString() override{
        return "pi";
    }

    virtual double evaluate() override{
        return 3.14159265358979323846;
    }
};

#endif
