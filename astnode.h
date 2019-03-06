#ifndef ASTNODE_H
#define ASTNODE_H

#include "errorhandling.h"
#include "numbers.h"
#include <math.h>

class AstNode{
public:
    virtual ~AstNode(){}
    virtual void deleteChildren() = 0;
    virtual std::string toString() = 0;
    virtual double evaluate() = 0;
    virtual AstNode* simplify(){return this;} // = 0;

protected:
    AstNode* getSimplifiedChild(AstNode* child){
        AstNode* simplified = child->simplify();
        if(simplified != child) delete child;

        return simplified;
    }
};

#endif // ASTNODE_H
