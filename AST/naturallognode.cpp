#include "naturallognode.h"

#include "eliteralnode.h"
#include "exponentnode.h"
#include "flatmultiplynode.h"
#include "rationalliteralnode.h"

NaturalLogNode::NaturalLogNode(AstNode* child)
    : UnaryNode(child){}

std::string NaturalLogNode::toString(){
    return "ln(" + child->toString() + ')';
}

double NaturalLogNode::evaluate(){
    return log(child->evaluate());
}

AstNode *NaturalLogNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.isOne()){
            //ln(1) => 0
            n->val = 0;
            return n;
        }else if(n->val.is_negative && !n->val.numerator.isZero()){
            error("Attempted to take log of negative number (" + n->toString() + ')');
        }
    }else if(eLiteralNode* n = dynamic_cast<eLiteralNode*>(child)){
        //ln(e) => 1
        delete n;
        return new RationalLiteralNode(1);
    }else if(ExponentNode* n = dynamic_cast<ExponentNode*>(child)){
        //ln(e^x) => x
        if(dynamic_cast<eLiteralNode*>(n->lhs)){
            AstNode* ans = n->rhs;
            delete n->lhs;
            delete n;
            return ans;
        }
    }else if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(child)){
        //ln(x*y) => ln(x) + ln(y) ... but you only want the change if it results in a simplification
    }

    return this;
}

NodeType NaturalLogNode::getType(){
    return NATURALLOG;
}
