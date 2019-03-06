#include "subtractnode.h"

#include "rationalliteralnode.h"

AstNode* SubtractNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* sub = new RationalLiteralNode(nl->val - nr->val);
        delete nl;
        delete nr;
        return sub;
    }

    return this;
}
