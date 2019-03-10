#include "naturallognode.h"

#include "rationalliteralnode.h"

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

AstNode *NaturalLogNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == n->val.denominator && n->val.numerator != big_uint("0")){
            n->val.numerator = big_uint("0");
            n->val.denominator = big_uint("1");
            n->val.is_negative = false;

            return n;
        }else if(n->val.is_negative && n->val.numerator != big_uint("0")){
            error("Attempted to take log of negative number (" + n->toString() + ')');
        }
    }

    return this;
}
