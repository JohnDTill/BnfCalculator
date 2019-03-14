#ifndef NARYNODE_H
#define NARYNODE_H

#include "../astnode.h"
#include <vector>
#include <functional>

class NAryNode : public AstNode{
public:
    std::vector<AstNode*> children;

public:
    void addChild(AstNode* n);
    virtual void deleteChildren() override;
    virtual void sortChildren() override;

protected:
    std::vector<AstNode*> select(std::function<bool(AstNode*)> predicate);
};

#endif // NARYNODE_H
