#ifndef LOGNODE_H
#define LOGNODE_H

#include "../astnode.h"

class LogNode : public AstNode{
private:
    AstNode* child;

public:
    LogNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // LOGNODE_H
