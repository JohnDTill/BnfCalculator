#include "additionnode.h"

#include "flatadditionnode.h"

AdditionNode::AdditionNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string AdditionNode::toString(){
    return lhs->toString(getPrecedence()) + " + " + rhs->toString(getPrecedence());
}

double AdditionNode::evaluate(){
    return lhs->evaluate() + rhs->evaluate();
}

AstNode* AdditionNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    FlatAdditionNode* n = new FlatAdditionNode;
    n->addFirst(lhs);
    n->addFirst(rhs);

    return n;
}

NodeType AdditionNode::getType(){
    return ADDITION;
}
