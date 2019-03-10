#include "lognode.h"

#include "rationalliteralnode.h"


LogNode::LogNode(AstNode* child){
    this->child = child;
}

void LogNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string LogNode::toString(){
    return "log(" + child->toString() + ')';
}

double LogNode::evaluate(){
    return log10(child->evaluate());
}

AstNode *LogNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == n->val.denominator && n->val.numerator != big_uint("0")){
            n->val.numerator = big_uint("0");
            n->val.denominator = big_uint("1");
            n->val.is_negative = false;

            return n;
        }else if(n->val.is_negative && n->val.numerator != big_uint("0")){
            error("Attempted to take log of negative number (" + n->toString() + ')');
        }
    }

    return this;
}
