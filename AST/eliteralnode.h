#ifndef ELITERALNODE_H
#define ELITERALNODE_H

#include "../astnode.h"

class eLiteralNode : public AstNode{
public:
    virtual void deleteChildren() override{}
    virtual std::string toString() override;
    virtual double evaluate() override;
};

#endif // ELITERALNODE_H
