#include "negatenode.h"

#include "rationalliteralnode.h"

NegateNode::NegateNode(AstNode* child)
    : UnaryNode(child){}

std::string NegateNode::toString(){
    return '-' + child->toString(getPrecedence());
}

double NegateNode::evaluate(){
    return -child->evaluate();
}

AstNode* NegateNode::simplify(){
    child = getSimplifiedChild(child);

    if(NegateNode* n = dynamic_cast<NegateNode*>(child)){
        AstNode* grandchild = n->child;
        delete n;
        return grandchild;
    }else if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        n->val.is_negative = !n->val.is_negative;
        return n;
    }

    return this;
}

NodeType NegateNode::getType(){
    return NEGATE;
}
