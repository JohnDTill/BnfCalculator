#ifndef GROUPINGNODE_H
#define GROUPINGNODE_H

#include "unarynode.h"

class GroupingNode : public UnaryNode{
public:
    GroupingNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
};

#endif // GROUPINGNODE_H
