#ifndef NUMBERLITERALNODE_H
#define NUMBERLITERALNODE_H

#include "../astnode.h"

class NumberLiteralNode : public AstNode{
private:
    std::string val;

public:
    NumberLiteralNode(std::string num_str);
    virtual void deleteChildren() override{}
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // NUMBERLITERALNODE_H
