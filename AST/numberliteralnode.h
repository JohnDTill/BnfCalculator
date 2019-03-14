#ifndef NUMBERLITERALNODE_H
#define NUMBERLITERALNODE_H

#include "terminalnode.h"

class NumberLiteralNode : public TerminalNode{
private:
    std::string val;

public:
    NumberLiteralNode(std::string num_str);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
};

#endif // NUMBERLITERALNODE_H
