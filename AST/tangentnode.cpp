#include "tangentnode.h"

#include "flatmultiplynode.h"
#include "nanliteralnode.h"
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
                rational arg = r->val % 2;
                if(r->val.is_negative) arg+=2;

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
                if(val=="1 / 2" || val=="3 / 2"){
                    n->deleteChildren();
                    delete n;

                    return new NanLiteralNode();
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
