#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "errorhandling.h"
#include "scanner.h"
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

            FlatAdditionNode* negate = new FlatAdditionNode;
            negate->addSecond(expr);
            return negate;
        }else{
            return rightUnary();
        }
    }

    AstNode* multiplication(){ //Left associative (only multiplication is commutative)
        AstNode* expr = leftUnary();

        while(peek(ASTRISK) || peek(BACKSLASH) || peek(FORWARDSLASH) || peek(PERCENT)){
            if(match(ASTRISK)){
                FlatMultiplyNode* node = new FlatMultiplyNode;
                node->addFirst(expr);
                node->addFirst(leftUnary());
                expr = node;
            }else if(match(BACKSLASH)){
                FlatMultiplyNode* node = new FlatMultiplyNode;
                node->addFirst(expr);
                node->addSecond(leftUnary());
                expr = node;
            }else if(match(FORWARDSLASH)){
                FlatMultiplyNode* node = new FlatMultiplyNode;
                node->addSecond(expr);
                node->addFirst(leftUnary());
                expr = node;
            }else if(match(PERCENT)){
                expr = new ModulusNode(expr, leftUnary());
            }
        }

        return expr;
    }

    AstNode* addition(){ //Left associative (subtraction is anti-commutative)
        AstNode* expr = multiplication();

        while(peek(PLUS) || peek(MINUS)){
            FlatAdditionNode* node = new FlatAdditionNode;
            node->addFirst(expr);

            if(match(PLUS)){
                node->addFirst(multiplication());
            }else if(match(MINUS)){
                node->addSecond(multiplication());
            }

            expr = node;
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

    static AstNode* parse(std::string source){
        return parse(Scanner::getTokenStream(source), source);
    }
};

inline AstNode* Parser::expression(){
    return addition();
}

#endif // PARSER_H
