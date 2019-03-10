#include "additionnode.h"

#include "rationalliteralnode.h"

AdditionNode::AdditionNode(AstNode* lhs, AstNode* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

void AdditionNode::deleteChildren(){
    lhs->deleteChildren();
    delete lhs;
    rhs->deleteChildren();
    delete rhs;
}

std::string AdditionNode::toString(){
    return lhs->toString() + " + " + rhs->toString();
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

    return this;
}
