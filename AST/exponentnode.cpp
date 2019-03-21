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
        rational result;
        bool found_num_root, found_denom_root, multiply_by_i;
        pow(nl->val, nr->val, result, found_num_root, found_denom_root, multiply_by_i);

        if(multiply_by_i) error("Imaginary square roots not supported.");

        if(found_num_root && found_denom_root){
            deleteChildren();
            return new RationalLiteralNode(result);
        }

        //DO THIS: several simplifications can be done for non-perfect roots
        //  -Handling perfect numerator or denominator
        //  -Finding perfect factors
    }

    return this;
}

NodeType ExponentNode::getType(){
    return EXPONENT;
}
