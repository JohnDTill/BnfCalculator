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
        if(n->val.numerator == big_uint("0") && n->val.denominator != big_uint("0")){
            return n;
        }
    }else if(PiLiteralNode* n = dynamic_cast<PiLiteralNode*>(child)){
        delete n;
        return new RationalLiteralNode(rational());
    }else if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(child)){
        if(n->children.size()==2){
            n->sortChildren();

            if(dynamic_cast<PiLiteralNode*>(n->children[0]))
            if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(n->children[1])){
                rational two(big_uint("2"), big_uint("1"), false);
                rational arg = r->val % two;
                if(r->val.is_negative) arg+=two;

                //DO THIS - rely on sine and cosine implementations
                std::unordered_map<std::string, std::string> exact_values = {
                    {"0", "0"},
                    {"1", "0"},
                    {"1 / 4", "1"},
                    {"3 / 4", "-1"},
                    {"5 / 4", "1"},
                    {"7 / 4", "-1"}
                };

                std::string val = arg.toString();
                if(val=="1 / 2"){
                    error("tan(pi/2) is undefined");
                }else if(val=="3 / 2"){
                    error("tan(-pi/2) is undefined");
                }

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

NodeType TangentNode::getType(){
    return TANGENT;
}
