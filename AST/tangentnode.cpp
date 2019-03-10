#include "tangentnode.h"

#include "rationalliteralnode.h"

TangentNode::TangentNode(AstNode* child){
    this->child = child;
}

void TangentNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string TangentNode::toString(){
    return "tan(" + child->toString() + ')';
}

double TangentNode::evaluate(){
    return tan(child->evaluate());
}

AstNode* TangentNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            return n;
        }
    }

    return this;
}
