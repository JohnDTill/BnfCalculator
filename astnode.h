#ifndef ASTNODE_H
#define ASTNODE_H

#include "errorhandling.h"
#include <math.h>

class AstNode{
public:
    virtual ~AstNode(){}
    virtual double evaluate() = 0;
};

//Literals
class NumberLiteralNode : public AstNode{
private:
    double val;

public:
    NumberLiteralNode(std::string num_str){
        val = std::atof(num_str.data());
    }

    virtual double evaluate() override{
        return val;
    }
};

//Unary nodes
class AbsoluteNode : public AstNode{
private:
    AstNode* child;

public:
    AbsoluteNode(AstNode* child){
        this->child = child;
    }

    virtual ~AbsoluteNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return abs(child->evaluate());
    }
};

class CosineNode : public AstNode{
private:
    AstNode* child;

public:
    CosineNode(AstNode* child){
        this->child = child;
    }

    virtual ~CosineNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return cos(child->evaluate());
    }
};

class FactorialNode : public AstNode{
private:
    AstNode* child;
    unsigned long long line;

public:
    FactorialNode(AstNode* child, unsigned long long line){
        this->child = child;
        this->line = line;
    }

    virtual ~FactorialNode() override{
        delete child;
    }

    virtual double evaluate() override{
        double val = child->evaluate();
        int rounded = static_cast<int>(val);
        double decimal_part = val - rounded;
        if(decimal_part > 1e-9 && 1-decimal_part > 1e-9)
            error("Factorial has non-integer argument");

        if(rounded < 0) error("Factorial has negative argument");

        int factorial = 1;
        for(int i = 2; i <= rounded; factorial *= i++);

        return factorial;
    }
};

class GroupingNode : public AstNode{
private:
    AstNode* child;

public:
    GroupingNode(AstNode* child){
        this->child = child;
    }

    virtual ~GroupingNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return child->evaluate();
    }
};

class LogNode : public AstNode{
private:
    AstNode* child;

public:
    LogNode(AstNode* child){
        this->child = child;
    }

    virtual ~LogNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return log10(child->evaluate());
    }
};

class NaturalLogNode : public AstNode{
private:
    AstNode* child;

public:
    NaturalLogNode(AstNode* child){
        this->child = child;
    }

    virtual ~NaturalLogNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return log(child->evaluate());
    }
};

class NegateNode : public AstNode{
private:
    AstNode* child;

public:
    NegateNode(AstNode* child){
        this->child = child;
    }

    virtual ~NegateNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return -child->evaluate();
    }
};

class SineNode : public AstNode{
private:
    AstNode* child;

public:
    SineNode(AstNode* child){
        this->child = child;
    }

    virtual ~SineNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return sin(child->evaluate());
    }
};

class TangentNode : public AstNode{
private:
    AstNode* child;

public:
    TangentNode(AstNode* child){
        this->child = child;
    }

    virtual ~TangentNode() override{
        delete child;
    }

    virtual double evaluate() override{
        return tan(child->evaluate());
    }
};

//Binary nodes
class AdditionNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    AdditionNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~AdditionNode() override{
        delete lhs;
        delete rhs;
    }

    virtual double evaluate() override{
        return lhs->evaluate() + rhs->evaluate();
    }
};

class DivideNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    DivideNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~DivideNode() override{
        delete lhs;
        delete rhs;
    }

    virtual double evaluate() override{
        return lhs->evaluate() / rhs->evaluate();
    }
};

class ExponentNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    ExponentNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~ExponentNode() override{
        delete lhs;
        delete rhs;
    }

    virtual double evaluate() override{
        return pow(lhs->evaluate(), rhs->evaluate());
    }
};

class ModulusNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    ModulusNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~ModulusNode() override{
        delete lhs;
        delete rhs;
    }

    virtual double evaluate() override{
        return fmod(lhs->evaluate(), rhs->evaluate());
    }
};

class MultiplyNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    MultiplyNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~MultiplyNode() override{
        delete lhs;
        delete rhs;
    }

    virtual double evaluate() override{
        return lhs->evaluate() * rhs->evaluate();
    }
};

class SubtractNode : public AstNode{
private:
    AstNode* lhs;
    AstNode* rhs;

public:
    SubtractNode(AstNode* lhs, AstNode* rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }

    virtual ~SubtractNode() override{
        delete lhs;
        delete rhs;
    }

    virtual double evaluate() override{
        return lhs->evaluate() - rhs->evaluate();
    }
};

#endif // ASTNODE_H
