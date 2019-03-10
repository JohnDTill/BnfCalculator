#include "groupingnode.h"

#include "absolutenode.h"
#include "cosinenode.h"
#include "negatenode.h"
#include "rationalliteralnode.h"

GroupingNode::GroupingNode(AstNode* child){
    this->child = child;
}

void GroupingNode::deleteChildren(){
    child->deleteChildren();
    delete child;
}

std::string GroupingNode::toString(){
    return '(' + child->toString() + ')';
}

double GroupingNode::evaluate(){
    return child->evaluate();
}

AstNode* GroupingNode::simplify(){
    child = getSimplifiedChild(child);

    //You might generally need a precedence ordering to map a tree to a string
    if(AbsoluteNode* n = dynamic_cast<AbsoluteNode*>(child)){
        return child;
    }else if(CosineNode* n = dynamic_cast<CosineNode*>(child)){
        return child;
    }else if(RationalLiteralNode* n = dynamic_cast<RationalLiteralNode*>(child)){
        return child;
    }

    return this;
}
