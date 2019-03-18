#ifndef FLATADDITIONNODE_H
#define FLATADDITIONNODE_H

#include "narynode.h"

class FlatAdditionNode : public NAryNode{
public:
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_ADDITION;}

private:
    void associateChildAdditions();
    AstNode* checkForNan();
    void combineRationalTerms();
    void cullZeroes();
};

#endif // FLATADDITIONNODE_H
