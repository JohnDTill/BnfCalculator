#include "exponentnode.h"

#include "rationalliteralnode.h"

ExponentNode::ExponentNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string ExponentNode::toString(){
    return lhs->toString(getPrecedence()) + '^' + rhs->toString(getPrecedence());
}

double ExponentNode::evaluate(){
    return pow(lhs->evaluate(), rhs->evaluate());
}

AstNode* ExponentNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        if(nr->val.isIntegerNumber()){
            bool is_negative = (nl->val.is_negative && nr->val.numerator.isOdd());
            bool reciprocal = nr->val.is_negative;
            rational exp = reciprocal ? rational(pow(nl->val.denominator,nr->val.numerator), pow(nl->val.numerator,nr->val.numerator), is_negative)
                                      : rational(pow(nl->val.numerator,nr->val.numerator), pow(nl->val.denominator,nr->val.numerator), is_negative);
            delete nl;
            delete nr;
            return new RationalLiteralNode(exp);
        }
    }

    return this;
}

NodeType ExponentNode::getType(){
    return EXPONENT;
}
