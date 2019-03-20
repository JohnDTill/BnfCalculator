#include "negatenode.h"

#include "flatadditionnode.h"

NegateNode::NegateNode(AstNode* child)
    : UnaryNode(child){}

std::string NegateNode::toString(){
    return '-' + child->toString(getPrecedence());
}

double NegateNode::evaluate(){
    return -child->evaluate();
}

AstNode* NegateNode::simplify(){
    child = getSimplifiedChild(child);

    FlatAdditionNode* n = new FlatAdditionNode;
    n->addSecond(child);

    return n;
}

NodeType NegateNode::getType(){
    return NEGATE;
}
