#ifndef SINENODE_H
#define SINENODE_H

#include "../astnode.h"

class SineNode : public AstNode{
private:
    AstNode* child;

public:
    SineNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // SINENODE_H
