#include "cosinenode.h"

#include "flatmultiplynode.h"
#include "piliteralnode.h"
#include "rationalliteralnode.h"
#include "../parser.h"

CosineNode::CosineNode(AstNode* child)
    : UnaryNode(child){}

std::string CosineNode::toString(){
    return "cos(" + child->toString() + ')';
}

double CosineNode::evaluate(){
    return cos(child->evaluate());
}

AstNode* CosineNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.isZero()){
            n->val = 1;

            return n;
        }
    }else if(PiLiteralNode* n = dynamic_cast<PiLiteralNode*>(child)){
        delete n;
        return new RationalLiteralNode(-1);
    }else if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(child)){
        if(n->first.size()==2 && n->second.size()==0){
            n->sortChildren();

            if(dynamic_cast<PiLiteralNode*>(n->first[0]))
            if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(n->first[1])){
                rational coeff = n->negate ? -r->val : r->val;
                std::string lookup = SineNode::lookupPiCoeff(coeff + rational(1,2));

                if(lookup.size() > 0){
                    deleteChildren();
                    return Parser::parse(lookup);
                }
            }
        }
    }

    return this;
}

NodeType CosineNode::getType(){
    return COSINE;
}
