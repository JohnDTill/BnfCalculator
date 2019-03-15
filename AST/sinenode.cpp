#include "sinenode.h"

#include "flatmultiplynode.h"
#include "piliteralnode.h"
#include "rationalliteralnode.h"
#include "../parser.h"
#include <unordered_map>

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
        if(n->children.size()==2){
            n->sortChildren();

            if(dynamic_cast<PiLiteralNode*>(n->children[0]))
            if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(n->children[1])){
                rational arg = r->val % 2;
                if(r->val.is_negative) arg+=2;

                std::unordered_map<std::string, std::string> exact_values = {
                    {"0", "0"},
                    {"1", "0"},
                    {"1 / 2", "1"},
                    {"-1 / 2", "-1"},
                    {"1 / 4", "1 / 2^(1/2)"},
                    {"3 / 4", "1 / 2^(1/2)"},
                    {"5 / 4", "-1 / 2^(1/2)"},
                    {"7 / 4", "-1 / 2^(1/2)"},
                    {"1 / 3", "3^(1/2)/2"},
                    {"2 / 3", "3^(1/2)/2"},
                    {"4 / 3", "-3^(1/2)/2"},
                    {"5 / 3", "-3^(1/2)/2"},
                    {"1 / 6", "1/2"},
                    {"5 / 6", "1/2"},
                    {"7 / 6", "-1/2"},
                    {"11 / 6", "-1/2"}
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

NodeType SineNode::getType(){
    return SINE;
}
