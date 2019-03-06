#include "additionnode.h"

#include "rationalliteralnode.h"

AstNode* AdditionNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* add = new RationalLiteralNode(nl->val + nr->val);
        delete nl;
        delete nr;
        return add;
    }

    return this;
}
