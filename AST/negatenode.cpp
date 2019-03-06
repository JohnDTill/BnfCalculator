#include "negatenode.h"

#include "rationalliteralnode.h"

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
