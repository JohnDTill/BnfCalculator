#ifndef GROUPINGNODE_H
#define GROUPINGNODE_H

#include "../astnode.h"

class GroupingNode : public AstNode{
private:
    AstNode* child;

public:
    GroupingNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // GROUPINGNODE_H
