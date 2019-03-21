#ifndef SINENODE_H
#define SINENODE_H

#include "unarynode.h"

#include <unordered_map>

class SineNode : public UnaryNode{
private:
    static const std::unordered_map<std::string, std::string> exact_values;

public:
    SineNode(AstNode* child);
    virtual std::string toString() override;
    virtual double evaluate() override;
    virtual AstNode* simplify() override;
    virtual NodeType getType() override;
    virtual Precedence getPrecedence() override {return PREC_NONE;}
    static std::string lookupPiCoeff(rational coeff);
};

#endif // SINENODE_H
