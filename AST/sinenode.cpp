#include "sinenode.h"

#include "flatmultiplynode.h"
#include "piliteralnode.h"
#include "rationalliteralnode.h"
#include "../parser.h"

const std::unordered_map<std::string, std::string> SineNode::exact_values = {
    {"0", "0"},
    {"1 / 12", "(2 - 3^(1/2))^(1/2)/2"},
    {"1 / 10", "(5^(1/2)-1)/4"},
    {"1 / 6", "1/2"},
    {"1 / 5", "2^(1/2)*(5 - 5^(1/2))/4"},
    {"1 / 4", "1 / 2^(1/2)"},
    {"3 / 10", "(5^(1/2)+1)/4"},
    {"1 / 3", "3^(1/2)/2"},
    {"2 / 5", "2^(1/2)*(5 + 5^(1/2))^(1/2)/4"},
    {"5 / 12", "(2 + 3^(1/2))^(1/2)/2"},
    {"1 / 2", "1"}
};

SineNode::SineNode(AstNode* child)
    : UnaryNode(child){}

std::string SineNode::toString(){
    return "sin(" + child->toString() + ')';
}

double SineNode::evaluate(){
    return sin(child->evaluate());
}

AstNode* SineNode::simplify(){
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
                std::string lookup = lookupPiCoeff(coeff);

                if(lookup.size() > 0){
                    deleteChildren();
                    return Parser::parse(lookup);
                }
            }
        }
    }

    return this;
}

NodeType SineNode::getType(){
    return SINE;
}

std::string SineNode::lookupPiCoeff(rational coeff){
    coeff %= 2;
    if(coeff.is_negative) coeff+=2;

    std::string str = "";
    if(coeff > rational(3,2)){
        str = "-";
        coeff = rational(2) - coeff;
    }else if(coeff > 1){
        str = "-";
        coeff -= 1;
    }else if(coeff > rational(1,2)){
        coeff = rational(1) - coeff;
    }

    auto result = exact_values.find(coeff.toString());
    if(result != exact_values.end()){
        str += result->second;
        return str;
    }else{
        return "";
    }
}
