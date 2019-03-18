#ifndef NANLITERALNODE_H
#define NANLITERALNODE_H

#include "terminalnode.h"

class NanLiteralNode : public TerminalNode{
public:
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual NodeType getType() override;
};

#endif // NANLITERALNODE_H
