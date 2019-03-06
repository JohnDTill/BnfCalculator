#include "groupingnode.h"

#include "absolutenode.h"
#include "cosinenode.h"
#include "negatenode.h"
#include "rationalliteralnode.h"

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
