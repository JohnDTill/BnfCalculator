#include "flatmultiplynode.h"

#include "exponentnode.h"
#include "nanliteralnode.h"
#include "negatenode.h"
#include "rationalliteralnode.h"

std::string FlatMultiplyNode::toString(){
    if(children.size()==0) error("FLATMULTIPLYNODE with no children.");

    std::string str = negate ? "-" : "";
    str += children[0]->toString();
    for(unsigned long long i = 1; i < children.size(); i++){
        if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(children[i])){
            if(n->val.numerator.isOne()){
                str += (n->val.is_negative ? "/-" : "/") + n->val.denominator.toString();
                continue;
            }
        }

        str += '*' + children[i]->toString(getPrecedence());
    }

    return str;
}

double FlatMultiplyNode::evaluate(){
    if(children.size()==0) error("FLATMULTIPLYNODE with no children.");

    double val = children[0]->evaluate();
    for(unsigned long long i = 1; i < children.size(); i++)
        val *= children[i]->evaluate();

    return val;
}

AstNode* FlatMultiplyNode::simplify(){
    simplifyChildren();
    associateChildMultiplications();
    if(AstNode* n = checkForNan()) return n;
    combineRationalTerms();
    combineNegations();
    cullOnes();
    if(AstNode* n = checkForZero()) return n;

    sortChildren();

    return this;
}

NodeType FlatMultiplyNode::getType(){
    return FLATMULTIPLY;
}

void FlatMultiplyNode::associateChildMultiplications(){
    for(unsigned long long i = 0; i < children.size(); i++){
        if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(children[i])){
            for(AstNode* nc : n->children) addChild(nc);

            children.erase(children.begin() + static_cast<long long>(i));
            if(n->negate) negate = !negate;
            delete n;
        }
    }
}

AstNode* FlatMultiplyNode::checkForNan(){
    if(select([](AstNode* n){return n->getType()==NANLITERAL;}).size() > 0){
        for(AstNode* child : children){
            child->deleteChildren();
            delete child;
        }

        return new NanLiteralNode();
    }else{
        return nullptr;
    }
}

void FlatMultiplyNode::combineRationalTerms(){
    std::vector<AstNode*> rational_nodes = select([](AstNode* n){return n->getType() == RATIONALLITERAL;});
    if(rational_nodes.size() > 1){
        rational val = static_cast<RationalLiteralNode*>(rational_nodes[0])->val;

        for(unsigned long long i = 1; i < rational_nodes.size(); i++){
            val *= static_cast<RationalLiteralNode*>(rational_nodes[i])->val;
            auto p = find(children.begin(), children.end(), rational_nodes[i]);
            children.erase(p);
            delete rational_nodes[i];
        }

        static_cast<RationalLiteralNode*>(rational_nodes[0])->val = val;
    }
}

void FlatMultiplyNode::cullOnes(){
    if(children.size() < 2) return;

    std::vector<AstNode*> rational_nodes = select([](AstNode* n){return n->getType() == RATIONALLITERAL;});
    if(rational_nodes.size() > 0){
        RationalLiteralNode* r = static_cast<RationalLiteralNode*>(rational_nodes[0]);
        if(r->val.isOne()){
            auto p = find(children.begin(), children.end(), r);
            children.erase(p);
            delete r;
        }
    }
}

AstNode *FlatMultiplyNode::checkForZero(){
    if(children.size() < 2) return nullptr;

    std::vector<AstNode*> rational_nodes = select([](AstNode* n){return n->getType() == RATIONALLITERAL;});
    if(rational_nodes.size() > 0){
        RationalLiteralNode* r = static_cast<RationalLiteralNode*>(rational_nodes[0]);
        if(r->val.isZero()){
            negate = false;
            for(AstNode* child : children){
                child->deleteChildren();
                delete child;
            }

            return new RationalLiteralNode(rational(0));
        }
    }

    return nullptr;
}

void FlatMultiplyNode::combineNegations(){
    for(unsigned long long i = 0; i < children.size(); i++){
        if(NegateNode* n = dynamic_cast<NegateNode*>(children[i])){
            children[i] = n->child;
            delete n;
            negate = !negate;
        }else if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(children[i])){
            if(n->val.is_negative){
                n->val.is_negative = false;
                negate = !negate;
            }
        }
    }
}
