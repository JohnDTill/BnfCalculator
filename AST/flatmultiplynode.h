#ifndef FLATMULTIPLYNODE_H
#define FLATMULTIPLYNODE_H

#include "doublenarynode.h"
class ExponentNode;

class FlatMultiplyNode : public DoubleNAryNode{
public:
    bool negate = false;

public:
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_MULTIPLICATION;}

private:
    void associateChildMultiplications();
    AstNode* checkForNan();
    void combineRationalTerms();
    void foldNegations();
    AstNode* checkForZero();
    void checkForCancellations();
};

#endif // FLATMULTIPLYNODE_H
