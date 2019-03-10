#include "dividenode.h"

#include "rationalliteralnode.h"

DivideNode::DivideNode(AstNode* lhs, AstNode* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

void DivideNode::deleteChildren(){
    lhs->deleteChildren();
    delete lhs;
    rhs->deleteChildren();
    delete rhs;
}

std::string DivideNode::toString(){
    return lhs->toString() + " / " + rhs->toString();
}

double DivideNode::evaluate(){
    return lhs->evaluate() / rhs->evaluate();
}

AstNode* DivideNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* div = new RationalLiteralNode(nl->val / nr->val);
        delete nl;
        delete nr;
        return div;
    }

    return this;
}
