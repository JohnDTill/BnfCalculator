#include "subtractnode.h"

#include "rationalliteralnode.h"

SubtractNode::SubtractNode(AstNode* lhs, AstNode* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

void SubtractNode::deleteChildren(){
    lhs->deleteChildren();
    delete lhs;
    rhs->deleteChildren();
    delete rhs;
}

std::string SubtractNode::toString(){
    return lhs->toString() + " - " + rhs->toString();
}

double SubtractNode::evaluate(){
    return lhs->evaluate() - rhs->evaluate();
}

AstNode* SubtractNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* sub = new RationalLiteralNode(nl->val - nr->val);
        delete nl;
        delete nr;
        return sub;
    }

    return this;
}
