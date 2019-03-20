#ifndef FLATADDITIONNODE_H
#define FLATADDITIONNODE_H

#include "doublenarynode.h"

class FlatAdditionNode : public DoubleNAryNode{
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
    void checkForCancellations();
};

#endif // FLATADDITIONNODE_H
