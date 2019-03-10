#include "sinenode.h"

#include "rationalliteralnode.h"

SineNode::SineNode(AstNode* child){
    this->child = child;
}

void SineNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string SineNode::toString(){
    return "sin(" + child->toString() + ')';
}

double SineNode::evaluate(){
    return sin(child->evaluate());
}

AstNode* SineNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            return n;
        }
    }

    return this;
}
