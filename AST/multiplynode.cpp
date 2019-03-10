#include "multiplynode.h"

#include "rationalliteralnode.h"

MultiplyNode::MultiplyNode(AstNode* lhs, AstNode* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

void MultiplyNode::deleteChildren(){
    lhs->deleteChildren();
    delete lhs;
    rhs->deleteChildren();
    delete rhs;
}

std::string MultiplyNode::toString(){
    return lhs->toString() + '*' + rhs->toString();
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

    return this;
}
