#include "rationalliteralnode.h"

#include "nanliteralnode.h"

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

AstNode* RationalLiteralNode::simplify(){
    if(val.denominator==0) return new NanLiteralNode();

    return this;
}

NodeType RationalLiteralNode::getType(){
    return RATIONALLITERAL;
}

Precedence RationalLiteralNode::getPrecedence(){
    if(!val.denominator.isOne()) return PREC_MULTIPLICATION;
    else return PREC_NONE;
}
