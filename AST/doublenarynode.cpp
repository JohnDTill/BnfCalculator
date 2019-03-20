#include "doublenarynode.h"

#include <algorithm>

void DoubleNAryNode::addFirst(AstNode* n){
    first.push_back(n);
}

void DoubleNAryNode::addSecond(AstNode* n){
    second.push_back(n);
}

void DoubleNAryNode::deleteChildren(){
    for(AstNode* child : first){
        child->deleteChildren();
        delete child;
    }
    for(AstNode* child : second){
        child->deleteChildren();
        delete child;
    }
}

static bool isLess(AstNode* a, AstNode* b){
    return a->sortsLowerThan(b);
}

void DoubleNAryNode::sortChildren(){
    std::sort(first.begin(), first.end(), isLess);
    std::sort(second.begin(), second.end(), isLess);
}

void DoubleNAryNode::simplifyChildren(){
    for(unsigned long long i = 0; i < first.size(); i++)
        first[i] = getSimplifiedChild(first[i]);
    for(unsigned long long i = 0; i < second.size(); i++)
        second[i] = getSimplifiedChild(second[i]);
}
