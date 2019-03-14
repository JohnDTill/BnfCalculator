#include "eliteralnode.h"

std::string eLiteralNode::toString(){
    return "e";
}

double eLiteralNode::evaluate(){
    return 2.71828182845904523536;
}

NodeType eLiteralNode::getType(){
    return eLITERAL;
}
