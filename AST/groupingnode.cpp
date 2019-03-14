#include "groupingnode.h"

#include "absolutenode.h"
#include "cosinenode.h"
#include "negatenode.h"
#include "rationalliteralnode.h"

GroupingNode::GroupingNode(AstNode* child)
    : UnaryNode(child){}

std::string GroupingNode::toString(){
    return '(' + child->toString() + ')';
}

double GroupingNode::evaluate(){
    return child->evaluate();
}

AstNode* GroupingNode::simplify(){
    return getSimplifiedChild(child);
}

NodeType GroupingNode::getType(){
    return GROUPING;
}
