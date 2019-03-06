#include "absolutenode.h"

#include "negatenode.h"
#include "rationalliteralnode.h"

AstNode* AbsoluteNode::simplify(){
    child = getSimplifiedChild(child);

    if(NegateNode* n = dynamic_cast<NegateNode*>(child)){
        child = n->child;
        delete n;
        return simplify();
    }else if(AbsoluteNode* n = dynamic_cast<AbsoluteNode*>(child)){
        child = n->child;
        delete n;
        return simplify();
    }else if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        n->val.is_negative = false;
        return n;
    }

    return this;
}
