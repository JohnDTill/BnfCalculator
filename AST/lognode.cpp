#include "lognode.h"

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
        if(n->val.isOne()){
            n->val = 0;

            return n;
        }else if(n->val.is_negative && !n->val.numerator.isZero()){
            error("Attempted to take log of negative number (" + n->toString() + ')');
        }
    }

    return this;
}

NodeType LogNode::getType(){
    return LOG;
}
