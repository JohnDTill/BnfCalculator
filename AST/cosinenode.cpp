#include "cosinenode.h"

#include "rationalliteralnode.h"

AstNode* CosineNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            n->val.numerator = big_uint("1");
            n->val.denominator = big_uint("1");
            n->val.is_negative = false;

            return n;
        }
    }

    return this;
}
