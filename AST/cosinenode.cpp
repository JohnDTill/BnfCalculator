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
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            n->val.numerator = big_uint("1");
            n->val.denominator = big_uint("1");
            n->val.is_negative = false;

            return n;
        }
    }else if(PiLiteralNode* n = dynamic_cast<PiLiteralNode*>(child)){
        delete n;
        return new RationalLiteralNode(rational(big_uint("1"),big_uint("1"),true));
    }else if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(child)){
        if(n->children.size()==2){
            n->sortChildren();

            if(dynamic_cast<PiLiteralNode*>(n->children[0]))
            if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(n->children[1])){
                rational two(big_uint("2"), big_uint("1"), false);
                rational arg = r->val % two;
                if(r->val.is_negative) arg+=two;

                std::unordered_map<std::string, std::string> exact_values = {
                    {"0", "1"},
                    {"1", "-1"},
                    {"1 / 2", "0"},
                    {"-1 / 2", "0"},
                    {"1 / 4", "1 / 2^(1/2)"},
                    {"7 / 4", "1 / 2^(1/2)"},
                    {"3 / 4", "-1 / 2^(1/2)"},
                    {"5 / 4", "-1 / 2^(1/2)"},
                    {"1 / 3", "1 / 2"},
                    {"5 / 3", "1 / 2"},
                    {"2 / 3", "-1 / 2"},
                    {"4 / 3", "-1 / 2"},
                    {"1 / 6", "3^(1/2)/2"},
                    {"11 / 6", "3^(1/2)/2"},
                    {"5 / 6", "-3^(1/2)/2"},
                    {"7 / 6", "-3^(1/2)/2"}
                };

                std::string val = arg.toString();
                auto result = exact_values.find(val);
                if(result != exact_values.end()){
                    n->deleteChildren();
                    delete n;
                    return Parser::parse(exact_values[val]);
                }
            }
        }
    }

    return this;
}

NodeType CosineNode::getType(){
    return COSINE;
}
