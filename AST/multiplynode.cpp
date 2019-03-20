#include "multiplynode.h"

#include "flatmultiplynode.h"

MultiplyNode::MultiplyNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string MultiplyNode::toString(){
    return lhs->toString(getPrecedence()) + '*' + rhs->toString(getPrecedence());
}

double MultiplyNode::evaluate(){
    return lhs->evaluate() * rhs->evaluate();
}

AstNode* MultiplyNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    FlatMultiplyNode* n = new FlatMultiplyNode;
    n->addFirst(lhs);
    n->addFirst(rhs);

    return n;
}

NodeType MultiplyNode::getType(){
    return MULTIPLY;
}
