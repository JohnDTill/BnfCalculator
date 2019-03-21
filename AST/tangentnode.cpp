#include "tangentnode.h"

#include "flatmultiplynode.h"
#include "piliteralnode.h"
#include "rationalliteralnode.h"
#include "../parser.h"

TangentNode::TangentNode(AstNode* child)
    : UnaryNode(child){}

std::string TangentNode::toString(){
    return "tan(" + child->toString() + ')';
}

double TangentNode::evaluate(){
    return tan(child->evaluate());
}

AstNode* TangentNode::simplify(){
    child = getSimplifiedChild(child);

    if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        if(n->val.isZero()){
            return n;
        }
    }else if(PiLiteralNode* n = dynamic_cast<PiLiteralNode*>(child)){
        delete n;
        return new RationalLiteralNode(0);
    }else if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(child)){
        if(n->first.size()==2 && n->second.size()==0){
            n->sortChildren();

            if(dynamic_cast<PiLiteralNode*>(n->first[0]))
            if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(n->first[1])){
                rational coeff = n->negate ? -r->val : r->val;
                std::string sine_lookup = SineNode::lookupPiCoeff(coeff);
                if(sine_lookup.size() > 0){
                    std::string cosine_lookup = SineNode::lookupPiCoeff(coeff + rational(1,2));
                    FlatMultiplyNode* result = new FlatMultiplyNode;
                    result->addFirst(Parser::parse(sine_lookup));
                    result->addSecond(Parser::parse(cosine_lookup));
                    deleteChildren();
                    return result;
                }
            }
        }
    }

    return this;
}

NodeType TangentNode::getType(){
    return TANGENT;
}
