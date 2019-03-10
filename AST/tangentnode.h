#ifndef TANGENTNODE_H
#define TANGENTNODE_H

#include "../astnode.h"

class TangentNode : public AstNode{
private:
    AstNode* child;

public:
    TangentNode(AstNode* child);
    virtual void deleteChildren() override;
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
};

#endif // TANGENTNODE_H
