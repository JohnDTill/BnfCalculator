#ifndef TERMINALNODE_H
#define TERMINALNODE_H

#include "../astnode.h"

class TerminalNode : public AstNode{
public:
    virtual void deleteChildren() override{}
    virtual void sortChildren() override{}
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // TERMINALNODE_H
