#include "subtractnode.h"

#include "additionnode.h"
#include "rationalliteralnode.h"

SubtractNode::SubtractNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string SubtractNode::toString(){
    return lhs->toString(getPrecedence()) + " - " + rhs->toString(getPrecedence());
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
    }else if(nr){
        nr->val.is_negative = !nr->val.is_negative;
        return new AdditionNode(lhs,rhs);
    }

    return this;
}

NodeType SubtractNode::getType(){
    return SUBTRACT;
}
