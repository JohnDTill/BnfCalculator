#ifndef LOGNODE_H
#define LOGNODE_H

#include "unarynode.h"

class LogNode : public UnaryNode{
public:
    LogNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // LOGNODE_H
