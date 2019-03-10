#include "cosinenode.h"

#include "rationalliteralnode.h"

CosineNode::CosineNode(AstNode* child){
    this->child = child;
}

void CosineNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string CosineNode::toString(){
    return "cos(" + child->toString() + ')';
}

double CosineNode::evaluate(){
    return cos(child->evaluate());
}

AstNode* CosineNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            n->val.numerator = big_uint("1");
            n->val.denominator = big_uint("1");
            n->val.is_negative = false;

            return n;
        }
    }

    return this;
}
