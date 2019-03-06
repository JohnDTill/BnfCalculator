#include "dividenode.h"

#include "rationalliteralnode.h"

AstNode* DivideNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* div = new RationalLiteralNode(nl->val / nr->val);
        delete nl;
        delete nr;
        return div;
    }

    return this;
}
