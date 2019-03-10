#include "naturallognode.h"


NaturalLogNode::NaturalLogNode(AstNode* child){
    this->child = child;
}

void NaturalLogNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string NaturalLogNode::toString(){
    return "ln(" + child->toString() + ')';
}

double NaturalLogNode::evaluate(){
    return log(child->evaluate());
}
