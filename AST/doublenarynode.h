#ifndef DOUBLENARYNODE_H
#define DOUBLENARYNODE_H

#include "../astnode.h"
#include <vector>
#include <functional>

class DoubleNAryNode : public AstNode{
public:
    std::vector<AstNode*> first;
    std::vector<AstNode*> second;

public:
    void addFirst(AstNode* n);
    void addSecond(AstNode* n);
    virtual void deleteChildren() override;
    virtual void sortChildren() override;
    void simplifyChildren();

protected:
    //std::vector<AstNode*> select(std::function<bool(AstNode*)> predicate);
};

#endif // DOUBLENARYNODE_H
