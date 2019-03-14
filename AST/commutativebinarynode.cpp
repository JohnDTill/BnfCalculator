#include "commutativebinarynode.h"

void CommutativeBinaryNode::sortChildren(){
    if(rhs->sortsLowerThan(lhs)){
        AstNode* temp = lhs;
        lhs = rhs;
        rhs = temp;
    }
}
