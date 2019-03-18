#ifndef ASTNODE_H
#define ASTNODE_H

#include "errorhandling.h"
#include "numbers.h"
#include <math.h>

enum NodeType{
    ABSOLUTE,
    ADDITION,
    COSINE,
    DIVIDE,
    eLITERAL,
    EXPONENT,
    FACTORIAL,
    FLATADDITION,
    FLATMULTIPLY,
    GROUPING,
    LOG,
    MODULUS,
    MULTIPLY,
    NANLITERAL,
    NATURALLOG,
    NEGATE,
    NUMBERLITERAL,
    piLITERAL,
    SINE,
    SUBTRACT,
    TANGENT,

    RATIONALLITERAL
};

enum Precedence{
    PREC_NONE,
    PREC_ADDITION,
    PREC_MULTIPLICATION,
    PREC_EXPONENTIATION,
    PREC_NEGATION,
    PREC_FACTORIAL
};

class AstNode{
public:
    virtual ~AstNode(){}
    virtual void deleteChildren() = 0;
    virtual std::string toString() = 0;
    virtual std::string toString(Precedence parent_precedence){
        if(parent_precedence > getPrecedence() && getPrecedence() != PREC_NONE) return '(' + toString() + ')';
        else return toString();
    }
    virtual double evaluate() = 0;
    virtual AstNode* simplify(){return this;} // = 0;
    virtual void sortChildren(){} // = 0;
    virtual NodeType getType() = 0;
    virtual Precedence getPrecedence() = 0;
    //virtual bool sortsLowerThanSame(AstNode* other) = 0;
    bool sortsLowerThan(AstNode* other){
        if(getType() != other->getType()) return getType() < other->getType();

        //DO THIS - continue making comparisons

        return false;
    }
    bool compareStrings(AstNode* other){
        return (getType()==other->getType() && toString() == other->toString());
    }

protected:
    AstNode* getSimplifiedChild(AstNode* child){
        AstNode* simplified = child->simplify();
        if(simplified != child){
            delete child;
            return getSimplifiedChild(simplified);
        }

        return simplified;
    }
};

#endif // ASTNODE_H
