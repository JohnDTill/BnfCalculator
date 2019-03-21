#include "piliteralnode.h"

std::string PiLiteralNode::toString(){
    return "pi";
}

double PiLiteralNode::evaluate(){
    return 3.14159265358979323846;
}

NodeType PiLiteralNode::getType(){
    return piLITERAL;
}
