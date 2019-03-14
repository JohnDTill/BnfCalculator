#include "binarynode.h"

BinaryNode::BinaryNode(AstNode* lhs, AstNode* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

void BinaryNode::deleteChildren(){
    lhs->deleteChildren();
    delete lhs;
    rhs->deleteChildren();
    delete rhs;
}
