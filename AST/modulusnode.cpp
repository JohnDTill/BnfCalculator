#include "modulusnode.h"

#include "rationalliteralnode.h"

ModulusNode::ModulusNode(AstNode* lhs, AstNode* rhs)
    : BinaryNode(lhs,rhs){}

std::string ModulusNode::toString(){
    return lhs->toString(getPrecedence()) + '%' + rhs->toString(getPrecedence());
}

double ModulusNode::evaluate(){
    return fmod(lhs->evaluate(), rhs->evaluate());
}

AstNode* ModulusNode::simplify(){
    lhs = getSimplifiedChild(lhs);
    rhs = getSimplifiedChild(rhs);

    RationalLiteralNode* nl = dynamic_cast<RationalLiteralNode*>(lhs);
    RationalLiteralNode* nr = dynamic_cast<RationalLiteralNode*>(rhs);
    if(nl && nr){
        RationalLiteralNode* mod = new RationalLiteralNode(nl->val % nr->val);
        mod->val.simplify();
        delete nl;
        delete nr;
        return mod;
    }

    return this;
}

NodeType ModulusNode::getType(){
    return MODULUS;
}

