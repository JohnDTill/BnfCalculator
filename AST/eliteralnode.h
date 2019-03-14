#ifndef ELITERALNODE_H
#define ELITERALNODE_H

#include "terminalnode.h"

class eLiteralNode : public TerminalNode{
public:
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual NodeType getType() override;
};

#endif // ELITERALNODE_H
