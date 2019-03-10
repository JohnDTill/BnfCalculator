#include "lognode.h"


LogNode::LogNode(AstNode* child){
    this->child = child;
}

void LogNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string LogNode::toString(){
    return "log(" + child->toString() + ')';
}

double LogNode::evaluate(){
    return log10(child->evaluate());
}
