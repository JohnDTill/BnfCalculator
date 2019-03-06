#include "multiplynode.h"

#include "rationalliteralnode.h"

AstNode* MultiplyNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* mult = new RationalLiteralNode(nl->val * nr->val);
        delete nl;
        delete nr;
        return mult;
    }

    return this;
}
