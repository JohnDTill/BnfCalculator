#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "errorhandling.h"
#include "token.h"

class AstNode;

class Parser{
private:
    unsigned long long size;
    unsigned long long curr = 0;
    std::vector<Token> token_stream;
    std::string source;

private:
    Parser(std::vector<Token> token_stream, std::string source){
        this->token_stream = token_stream;
        this->source = source;
        size = token_stream.size();
    }

    void advance(){
        curr++;
    }

    bool peek(TokenType t){
        return curr < size && token_stream[curr].type == t;
    }

    bool match(TokenType t){
        if(peek(t)){
            advance();
            return true;
        }else{
            return false;
        }
    }

    void consume(TokenType t){
        if(!match(t)){
            error("Parser Error");
        }
    }

    AstNode* expression();

    AstNode* identifier(){
        if(match(e_CONSTANT)){
            return new eLiteralNode;
        }else if(match(PI)){
            return new PiLiteralNode;
        }else if(match(COS)){
            consume(LEFT_PAREN);
            AstNode* expr = expression();
            consume(RIGHT_PAREN);
            return new CosineNode(expr);
        }else if(match(LOG10)){
            consume(LEFT_PAREN);
            AstNode* expr = expression();
            consume(RIGHT_PAREN);
            return new LogNode(expr);
        }else if(match(NATURAL_LOG)){
            consume(LEFT_PAREN);
            AstNode* expr = expression();
            consume(RIGHT_PAREN);
            return new NaturalLogNode(expr);
        }else if(match(SIN)){
            consume(LEFT_PAREN);
            AstNode* expr = expression();
            consume(RIGHT_PAREN);
            return new SineNode(expr);
        }else if(match(TAN)){
            consume(LEFT_PAREN);
            AstNode* expr = expression();
            consume(RIGHT_PAREN);
            return new TangentNode(expr);
        }else{
            error("Unhandled Identifier case.");
        }
    }

    AstNode* numberLiteral(){
        if(match(NUMBER_LITERAL)){
            Token t = token_stream[curr-1];
            std::string num_str = source.substr(t.start, t.size);

            return new NumberLiteralNode(num_str);
        }else{
            return identifier();
        }
    }

    AstNode* grouping(){
        if(match(LEFT_PAREN)){
            AstNode* expr = expression();
            consume(RIGHT_PAREN);
            return new GroupingNode(expr);
        }else if(match(UPRIGHTSLASH)){
            AstNode* expr = expression();
            consume(UPRIGHTSLASH);
            return new AbsoluteNode(expr);
        }else{
            return numberLiteral();
        }
    }

    AstNode* exponent(){ //Right associative
        AstNode* expr = grouping();
        if(match(CAROT)){ return new ExponentNode(expr, leftUnary()); }
        else return expr;
    }

    AstNode* rightUnary(){
        AstNode* expr = exponent();
        while(match(EXCLAMATION)){ expr = new FactorialNode(expr, token_stream[curr-1].line); }

        return expr;
    }

    AstNode* leftUnary(){
        if(match(MINUS)){
            AstNode* expr = leftUnary();

            return new NegateNode(expr);
        }else{
            return rightUnary();
        }
    }

    AstNode* multiplication(){ //Left associative (only multiplication is commutative)
        AstNode* expr = leftUnary();

        while(peek(ASTRISK) || peek(BACKSLASH) || peek(FORWARDSLASH) || peek(MODULUS)){
            if(match(ASTRISK)){
                expr = new MultiplyNode(expr, leftUnary());
            }else if(match(BACKSLASH)){
                expr = new DivideNode(expr, leftUnary());
            }else if(match(FORWARDSLASH)){
                expr = new DivideNode(leftUnary(), expr);
            }else if(match(MODULUS)){
                expr = new ModulusNode(expr, leftUnary());
            }
        }

        return expr;
    }

    AstNode* addition(){ //Left associative (subtraction is anti-commutative)
        AstNode* expr = multiplication();

        while(peek(PLUS) || peek(MINUS)){
            if(match(PLUS)){
                expr = new AdditionNode(expr, multiplication());
            }else if(match(MINUS)){
                expr = new SubtractNode(expr, multiplication());
            }
        }

        return expr;
    }

public:
    static AstNode* parse(std::vector<Token> token_stream, std::string source){
        Parser p(token_stream, source);
        AstNode* expr = p.expression();
        if(p.curr!=token_stream.size()) error("Parser Error");
        return expr;
    }
};

AstNode* Parser::expression(){
    return addition();
}

#endif // PARSER_H
