#include "subtractnode.h"

#include "flatadditionnode.h"

SubtractNode::SubtractNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string SubtractNode::toString(){
    return lhs->toString(getPrecedence()) + " - " + rhs->toString(getPrecedence());
}

double SubtractNode::evaluate(){
    return lhs->evaluate() - rhs->evaluate();
}

AstNode* SubtractNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    FlatAdditionNode* n = new FlatAdditionNode;
    n->addFirst(lhs);
    n->addSecond(rhs);

    return n;
}

NodeType SubtractNode::getType(){
    return SUBTRACT;
}
