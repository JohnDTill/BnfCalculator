#include "sinenode.h"

#include "rationalliteralnode.h"

AstNode* SineNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            return n;
        }
    }

    return this;
}
