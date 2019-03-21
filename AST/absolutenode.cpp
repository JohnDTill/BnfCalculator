#include "absolutenode.h"

#include "flatadditionnode.h"
#include "rationalliteralnode.h"

AbsoluteNode::AbsoluteNode(AstNode* child)
    : UnaryNode(child){}

std::string AbsoluteNode::toString(){
    return '|' + child->toString(getPrecedence()) + '|';
}

double AbsoluteNode::evaluate(){
    return abs(child->evaluate());
}

AstNode* AbsoluteNode::simplify(){
    child = getSimplifiedChild(child);

    if(AbsoluteNode* n = dynamic_cast<AbsoluteNode*>(child)){
        child = n->child;
        delete n;
        return simplify();
    }else if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        n->val.is_negative = false;
        return n;
    }

    double estimated_value = child->evaluate();
    if(estimated_value > 1e-12){
        return child;
    }else if(estimated_value < -1e-12){
        FlatAdditionNode* negate = new FlatAdditionNode;
        negate->addSecond(child);
        return negate;
    }

    return this;
}

NodeType AbsoluteNode::getType(){
    return ABSOLUTE;
}
