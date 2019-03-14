#include "dividenode.h"

#include "flatmultiplynode.h"
#include "negatenode.h"
#include "rationalliteralnode.h"

DivideNode::DivideNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string DivideNode::toString(){
    return lhs->toString(getPrecedence()) + " / " + rhs->toString(getPrecedence());
}

double DivideNode::evaluate(){
    return lhs->evaluate() / rhs->evaluate();
}

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
    }else if(nr){
        FlatMultiplyNode* m = new FlatMultiplyNode();
        if(NegateNode* nl = dynamic_cast<NegateNode*>(lhs)){
            RationalLiteralNode* recip = new RationalLiteralNode(rational(nr->val.denominator, nr->val.numerator, !nr->val.is_negative));
            m->addChild(nl->child);
            delete nl;
            m->addChild(recip);
        }else{
            RationalLiteralNode* recip = new RationalLiteralNode(rational(nr->val.denominator, nr->val.numerator, nr->val.is_negative));
            m->addChild(lhs);
            m->addChild(recip);
        }
        delete nr;
        return m;
    }

    return this;
}

NodeType DivideNode::getType(){
    return DIVIDE;
}
