#include "unarynode.h"

UnaryNode::UnaryNode(AstNode* child){
    this->child = child;
}

void UnaryNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}
