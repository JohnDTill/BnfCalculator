#include "nanliteralnode.h"

#include <limits>

std::string NanLiteralNode::toString(){
    return "NaN";
}

double NanLiteralNode::evaluate(){
    return std::numeric_limits<double>::quiet_NaN();
}

NodeType NanLiteralNode::getType(){
    return NANLITERAL;
}
