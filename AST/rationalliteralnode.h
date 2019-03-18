#ifndef RATIONALLITERALNODE_H
#define RATIONALLITERALNODE_H

#include "terminalnode.h"

class RationalLiteralNode : public TerminalNode{
public:
    rational val;

public:
    RationalLiteralNode(rational val);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override;
};

#endif // RATIONALLITERALNODE_H
