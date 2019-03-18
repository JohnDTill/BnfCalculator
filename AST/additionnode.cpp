#include "additionnode.h"

#include "flatadditionnode.h"
#include "rationalliteralnode.h"

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

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* add = new RationalLiteralNode(nl->val + nr->val);
        delete nl;
        delete nr;
        return add;
    }

    FlatAdditionNode* n = new FlatAdditionNode;
    n->addChild(lhs);
    n->addChild(rhs);

    return n;
}

NodeType AdditionNode::getType(){
    return ADDITION;
}
