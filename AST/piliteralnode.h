#ifndef PiLiteralNode_H
#define PiLiteralNode_H

#include "terminalnode.h"

class PiLiteralNode : public TerminalNode{
public:
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual NodeType getType() override;
};

#endif
