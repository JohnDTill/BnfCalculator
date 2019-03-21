#include "lognode.h"

#include "exponentnode.h"
#include "nanliteralnode.h"
#include "rationalliteralnode.h"

LogNode::LogNode(AstNode* child)
    : UnaryNode(child){}

std::string LogNode::toString(){
    return "log(" + child->toString() + ')';
}

double LogNode::evaluate(){
    return log10(child->evaluate());
}

AstNode *LogNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator.isZero()){} //Math library returns negative inf
        if(n->val.is_negative) return new NanLiteralNode();
        if(n->val.denominator != 1) return this;

        unsigned long long log_val;

        if(n->val.numerator.log(log_val)){
            n->val.numerator = log_val;
            return n;
        }
    }else if(ExponentNode* n = dynamic_cast<ExponentNode*>(child)){
        //log(10^x) => x
        if(RationalLiteralNode* lhs = dynamic_cast<RationalLiteralNode*>(n->lhs)){
            if(lhs->val == 10){
                AstNode* ans = n->rhs;
                delete lhs;
                delete n;
                return ans;
            }
        }
    }

    return this;
}

NodeType LogNode::getType(){
    return LOG;
}
