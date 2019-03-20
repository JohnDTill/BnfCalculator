#include "dividenode.h"

#include "flatmultiplynode.h"

DivideNode::DivideNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string DivideNode::toString(){
    return lhs->toString(getPrecedence()) + " / " + rhs->toString(getPrecedence());
}

double DivideNode::evaluate(){
    return lhs->evaluate() / rhs->evaluate();
}

AstNode* DivideNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    FlatMultiplyNode* n = new FlatMultiplyNode;
    n->addFirst(lhs);
    n->addSecond(rhs);

    return n;
}

NodeType DivideNode::getType(){
    return DIVIDE;
}
