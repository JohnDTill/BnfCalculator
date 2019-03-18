#ifndef FLATMULTIPLYNODE_H
#define FLATMULTIPLYNODE_H

#include "narynode.h"
class ExponentNode;

class FlatMultiplyNode : public NAryNode{
private:
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
    void cullOnes();
    AstNode* checkForZero();
    void combineNegations();
};

#endif // FLATMULTIPLYNODE_H
