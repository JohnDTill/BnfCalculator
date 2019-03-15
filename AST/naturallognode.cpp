#include "naturallognode.h"

#include "rationalliteralnode.h"

NaturalLogNode::NaturalLogNode(AstNode* child)
    : UnaryNode(child){}

std::string NaturalLogNode::toString(){
    return "ln(" + child->toString() + ')';
}

double NaturalLogNode::evaluate(){
    return log(child->evaluate());
}

AstNode *NaturalLogNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.isOne()){
            n->val = 0;

            return n;
        }else if(n->val.is_negative && !n->val.numerator.isZero()){
            error("Attempted to take log of negative number (" + n->toString() + ')');
        }
    }

    return this;
}

NodeType NaturalLogNode::getType(){
    return NATURALLOG;
}
