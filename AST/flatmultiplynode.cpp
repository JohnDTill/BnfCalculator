#include "flatmultiplynode.h"

#include "exponentnode.h"
#include "flatadditionnode.h"
#include "nanliteralnode.h"
#include "rationalliteralnode.h"

std::string FlatMultiplyNode::toString(){
    if(first.size()+second.size()==0) error("FLATMULTIPLYNODE with no children.");

    std::string str = first.size() > 0 ? first[0]->toString() : "1";
    for(unsigned long long i = 1; i < first.size(); i++){
        if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(first[i])){
            if(n->val.numerator.isOne()){
                str += (n->val.is_negative ? "/-" : "/") + n->val.denominator.toString();
                continue;
            }
        }

        str += '*' + first[i]->toString(getPrecedence());
    }
    if(second.size() == 1) str += " / " + second[0]->toString(getPrecedence());
    else if(second.size() > 1){
        str += " / (" + second[0]->toString(getPrecedence());
        for(unsigned long long i = 1; i < second.size(); i++)
            str += '*' + second[i]->toString(getPrecedence());
        str += ')';
    }

    return str;
}

double FlatMultiplyNode::evaluate(){
    if(first.size()+second.size()==0) error("FLATMULTIPLYNODE with no children.");

    double val = 1;
    for(AstNode* c : first)
        val *= c->evaluate();
    for(AstNode* c : second)
        val /= c->evaluate();

    return val;
}

AstNode* FlatMultiplyNode::simplify(){
    simplifyChildren();
    associateChildMultiplications();
    if(AstNode* n = checkForNan()) return n;
    foldNegations();
    combineRationalTerms();
    if(AstNode* n = checkForZero()) return n;
    checkForCancellations();
    if(first.size()+second.size() == 1) return first.size()==1 ? first[0] : this;
    if(first.size()+second.size() == 0) return new RationalLiteralNode(1);

    sortChildren();

    return this;
}

NodeType FlatMultiplyNode::getType(){
    return FLATMULTIPLY;
}

void FlatMultiplyNode::associateChildMultiplications(){
    for(unsigned long long i = 0; i < first.size(); i++){
        if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(first[i])){
            for(AstNode* nc : n->first) addFirst(nc);
            for(AstNode* nc : n->second) addSecond(nc);

            first.erase(first.begin() + static_cast<long long>(i));
            i--;
            delete n;
        }
    }
    for(unsigned long long i = 0; i < second.size(); i++){
        if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(second[i])){
            for(AstNode* nc : n->first) addSecond(nc);
            for(AstNode* nc : n->second) addFirst(nc);

            second.erase(second.begin() + static_cast<long long>(i));
            i--;
            delete n;
        }
    }
}

AstNode* FlatMultiplyNode::checkForNan(){
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
        if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(c)){
            if(r->val.isZero()){
                deleteChildren();
                return new NanLiteralNode();
            }
        }
    }

    return nullptr;
}

void FlatMultiplyNode::foldNegations(){
    bool negate = false;

    for(unsigned long long i = 0; i < first.size(); i++){
        if(FlatAdditionNode* n = dynamic_cast<FlatAdditionNode*>(first[i])){
            if(n->first.size()==0 && n->second.size()==1){
                negate = !negate;
                first[i] = n->second[0];
                delete n;
            }
        }
    }

    for(unsigned long long i = 0; i < second.size(); i++){
        if(FlatAdditionNode* n = dynamic_cast<FlatAdditionNode*>(second[i])){
            if(n->first.size()==0 && n->second.size()==1){
                negate = !negate;
                second[i] = n->second[0];
                delete n;
            }
        }
    }

    if(negate) addFirst(new RationalLiteralNode(-1)); //Kind of an annoying way to deal with negation
}

void FlatMultiplyNode::combineRationalTerms(){
    rational product = 1;

    for(unsigned long long i = 0; i < first.size(); i++){
        if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(first[i])){
            product *= r->val;
            first.erase(first.begin() + static_cast<long long>(i));
            i--;
            delete r;
        }
    }

    for(unsigned long long i = 0; i < second.size(); i++){
        if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(second[i])){
            product /= r->val;
            second.erase(second.begin() + static_cast<long long>(i));
            i--;
            delete r;
        }
    }

    if(!product.isOne()) addFirst(new RationalLiteralNode(product));
}

AstNode* FlatMultiplyNode::checkForZero(){
    if(first.size()+second.size() < 2) return nullptr;

    for(unsigned long long i = 0; i < first.size(); i++){
        if(RationalLiteralNode* r = dynamic_cast<RationalLiteralNode*>(first[i])){
            if(r->val.isZero()) return r;
        }
    }

    return nullptr;
}

void FlatMultiplyNode::checkForCancellations(){
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
