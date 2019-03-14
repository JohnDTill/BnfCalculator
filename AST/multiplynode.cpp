#include "multiplynode.h"

#include "flatmultiplynode.h"
#include "rationalliteralnode.h"

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

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* mult = new RationalLiteralNode(nl->val * nr->val);
        delete nl;
        delete nr;
        return mult;
    }

    FlatMultiplyNode* n = new FlatMultiplyNode;
    n->addChild(lhs);
    n->addChild(rhs);

    return n;
}

NodeType MultiplyNode::getType(){
    return MULTIPLY;
}
