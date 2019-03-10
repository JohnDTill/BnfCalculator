#include "rationalliteralnode.h"


RationalLiteralNode::RationalLiteralNode(rational val){
    this->val = val;
}

std::string RationalLiteralNode::toString(){
    return val.toString();
}

double RationalLiteralNode::evaluate(){
    double magnitude = std::atoi(val.numerator.toString().data()) / static_cast<double>(std::atoi(val.denominator.toString().data()));
    return val.is_negative ? -magnitude : magnitude;
}
