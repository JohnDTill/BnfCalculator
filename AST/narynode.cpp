#include "narynode.h"

#include <algorithm>

void NAryNode::addChild(AstNode* n){
    children.push_back(n);
}

void NAryNode::deleteChildren(){
    for(AstNode* child : children){
        child->deleteChildren();
        delete child;
    }
}

static bool isLess(AstNode* a, AstNode* b){
    return a->sortsLowerThan(b);
}

void NAryNode::sortChildren(){
    std::sort(children.begin(), children.end(), isLess);
}

void NAryNode::simplifyChildren(){
    for(unsigned long long i = 0; i < children.size(); i++)
        children[i] = getSimplifiedChild(children[i]);
}

std::vector<AstNode*> NAryNode::select(std::function<bool(AstNode*)> predicate){
    std::vector<AstNode*> found;
    for(AstNode* child : children){
        if(predicate(child)) found.push_back(child);
    }

    return found;
}
