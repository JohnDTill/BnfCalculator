#include "flatadditionnode.h"

#include "flatmultiplynode.h"
#include "nanliteralnode.h"
#include "rationalliteralnode.h"

std::string FlatAdditionNode::toString(){
    if(first.size()==0 && second.size()==0) error("FLATADDITIONNODE with no children.");

    std::string str = first.size() > 0 ? first[0]->toString(getPrecedence()) : "";
    for(unsigned long long i = 1; i < first.size(); i++){
        if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(first[i])){
            if(n->val.is_negative){
                str += '-' + (-n->val).toString();
                continue;
            }
        }

        str += '+' + first[i]->toString(getPrecedence());
    }
    for(unsigned long long i = 0; i < second.size(); i++){
        str += '-' + second[i]->toString(getPrecedence());
    }

    return str;
}

double FlatAdditionNode::evaluate(){
    if(first.size()==0 && second.size()==0) error("FLATADDITIONNODE with no children.");

    double val = 0;
    for(unsigned long long i = 0; i < first.size(); i++)
        val += first[i]->evaluate();
    for(unsigned long long i = 0; i < second.size(); i++)
        val -= second[i]->evaluate();

    return val;
}

AstNode* FlatAdditionNode::simplify(){
    simplifyChildren();
    associateChildAdditions();
    if(AstNode* n = checkForNan()) return n;
    combineRationalTerms();
    checkForCancellations();
    if(first.size() == 1 && second.size() == 0) return first[0];
    if(first.size()+second.size() == 0) return new RationalLiteralNode(0);

    sortChildren();

    return this;
}

NodeType FlatAdditionNode::getType(){
    return FLATADDITION;
}

void FlatAdditionNode::associateChildAdditions(){
    for(unsigned long long i = 0; i < first.size(); i++){
        if(FlatAdditionNode* n = dynamic_cast<FlatAdditionNode*>(first[i])){
            for(AstNode* nc : n->first) addFirst(nc);
            for(AstNode* nc : n->second) addSecond(nc);

            first.erase(first.begin() + static_cast<long long>(i));
            i--;
            delete n;
        }
    }
    for(unsigned long long i = 0; i < second.size(); i++){
        if(FlatAdditionNode* n = dynamic_cast<FlatAdditionNode*>(second[i])){
            for(AstNode* nc : n->first) addSecond(nc);
            for(AstNode* nc : n->second) addFirst(nc);

            second.erase(second.begin() + static_cast<long long>(i));
            i--;
            delete n;
        }else if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(second[i])){
            if(n->negate){
                n->negate = false;
                second.erase(second.begin() + static_cast<long long>(i));
                i--;
                first.push_back(n);
            }
        }
    }
}

AstNode* FlatAdditionNode::checkForNan(){
    for(AstNode* c : first){
        if(c->getType()==NANLITERAL){
            deleteChildren();
            return new NanLiteralNode();
        }
    }
    for(AstNode* c : second){
        if(c->getType()==NANLITERAL){
            deleteChildren();
            return new NanLiteralNode();
        }
    }

    return nullptr;
}

void FlatAdditionNode::combineRationalTerms(){
    rational sum = 0;

    for(unsigned long long i = 0; i < first.size(); i++){
        if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(first[i])){
            sum += r->val;
            first.erase(first.begin() + static_cast<long long>(i));
            i--;
            delete r;
        }
    }

    for(unsigned long long i = 0; i < second.size(); i++){
        if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(second[i])){
            sum -= r->val;
            second.erase(second.begin() + static_cast<long long>(i));
            i--;
            delete r;
        }
    }

    if(!sum.isZero()) addFirst(new RationalLiteralNode(sum));
}

void FlatAdditionNode::checkForCancellations(){
    for(unsigned long long i = 0; i < first.size(); i++){
        for(unsigned long long j = 0; j < second.size(); j++){
            if(first[i]->compareStrings(second[j])){
                AstNode* temp = first[i];
                first.erase(first.begin() + static_cast<long long>(i));
                i--;
                delete temp;

                temp = second[j];
                second.erase(second.begin() + static_cast<long long>(j));
                delete temp;

                break;
            }
        }
    }
}
