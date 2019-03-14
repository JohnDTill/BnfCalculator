#include "flatmultiplynode.h"

#include "rationalliteralnode.h"

std::string FlatMultiplyNode::toString(){
    if(children.size()==0) error("FLATMULTIPLYNODE with no children.");

    std::string str = children[0]->toString();
    for(unsigned long long i = 1; i < children.size(); i++)
        str += '*' + children[i]->toString(getPrecedence());

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
    for(unsigned long long i = 0; i < children.size(); i++){
        children[i] = getSimplifiedChild(children[i]);

        if(FlatMultiplyNode* n = dynamic_cast<FlatMultiplyNode*>(children[i])){
            for(AstNode* nc : n->children) addChild(nc);

            children.erase(children.begin() + static_cast<long long>(i));
            delete n;
        }
    }

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

    return this;
}

NodeType FlatMultiplyNode::getType(){
    return FLATMULTIPLY;
}
