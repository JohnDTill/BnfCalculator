#include "flatadditionnode.h"

#include "nanliteralnode.h"
#include "rationalliteralnode.h"

std::string FlatAdditionNode::toString(){
    if(children.size()==0) error("FLATADDITIONNODE with no children.");

    std::string str = children[0]->toString();
    for(unsigned long long i = 1; i < children.size(); i++){
        if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(children[i])){
            if(n->val.is_negative){
                str += '-' + (-n->val).toString();
                continue;
            }
        }

        str += '+' + children[i]->toString(getPrecedence());
    }

    return str;
}

double FlatAdditionNode::evaluate(){
    if(children.size()==0) error("FLATADDITIONNODE with no children.");

    double val = children[0]->evaluate();
    for(unsigned long long i = 1; i < children.size(); i++)
        val += children[i]->evaluate();

    return val;
}

AstNode* FlatAdditionNode::simplify(){
    simplifyChildren();
    associateChildAdditions();
    if(AstNode* n = checkForNan()) return n;
    combineRationalTerms();
    cullZeroes();

    sortChildren();

    return this;
}

NodeType FlatAdditionNode::getType(){
    return FLATADDITION;
}

void FlatAdditionNode::associateChildAdditions(){
    for(unsigned long long i = 0; i < children.size(); i++){
        if(FlatAdditionNode* n = dynamic_cast<FlatAdditionNode*>(children[i])){
            for(AstNode* nc : n->children) addChild(nc);

            children.erase(children.begin() + static_cast<long long>(i));
            delete n;
        }
    }
}

AstNode* FlatAdditionNode::checkForNan(){
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

void FlatAdditionNode::combineRationalTerms(){
std::vector<AstNode*> rational_nodes = select([](AstNode* n){return n->getType() == RATIONALLITERAL;});
    if(rational_nodes.size() > 1){
        rational val = static_cast<RationalLiteralNode*>(rational_nodes[0])->val;

        for(unsigned long long i = 1; i < rational_nodes.size(); i++){
            val += static_cast<RationalLiteralNode*>(rational_nodes[i])->val;
            auto p = find(children.begin(), children.end(), rational_nodes[i]);
            children.erase(p);
            delete rational_nodes[i];
        }

        static_cast<RationalLiteralNode*>(rational_nodes[0])->val = val;
    }
}

void FlatAdditionNode::cullZeroes(){
    if(children.size() < 2) return;

    std::vector<AstNode*> rational_nodes = select([](AstNode* n){return n->getType() == RATIONALLITERAL;});
    if(rational_nodes.size() > 0){
        RationalLiteralNode* r = static_cast<RationalLiteralNode*>(rational_nodes[0]);
        if(r->val.isZero()){
            auto p = find(children.begin(), children.end(), r);
            children.erase(p);
            delete r;
        }
    }
}
