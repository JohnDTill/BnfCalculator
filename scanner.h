#ifndef SCANNER_H
#define SCANNER_H

#include "errorhandling.h"
#include "token.h"

#include <string>
#include <vector>

class Scanner{
private:
    std::string source;
    unsigned long long size;
    std::vector<Token> token_stream;
    unsigned long long curr = 0;
    unsigned long long start = 0;
    unsigned int line = 0;

private:
    Scanner(std::string source){
        this->source = source;
        size = source.size();
    }

    void emitToken(const TokenType type){
        Token t;
        t.type = type;
        t.start = start;
        t.size = curr - start + 1;
        t.line = line;
        token_stream.push_back(t);

        start = curr+1;
    }

    bool isEnglishLetter(char c){
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isNumber(char c){
        return c >= '0' && c <= '9';
    }

    bool isAlphaNumeric(char c){
        return isEnglishLetter(c) || isNumber(c);
    }

    void parseNumber(){
        bool found_decimal = false;
        while(++curr < size){
            char c = source[curr];

            if(c == '.'){
                if(found_decimal){
                    error("Number has multiple decimals");
                }else{
                    found_decimal = true;
                    if(++curr >= size || !isNumber(source[curr]))
                        error("Number ends on decimal");
                }
            }else if(!isNumber(c)){
                break;
            }
        }
        curr--;

        emitToken(NUMBER_LITERAL);
    }

    void parseIdentifier(){
        while(++curr < size && isAlphaNumeric(source[curr])){ /* Do nothing */ }
        curr--;

        auto lookup = keywords.find(source.substr(start, curr-start+1));
        if(lookup == keywords.end()) error("Unrecognized keyword \"" + source.substr(start, curr-start+1) + "\"");
        emitToken(lookup->second);
    }

    void processChar(char c){
        if(c=='\n'){
            emitToken(NEWLINE);
            line++;
            return;
        }else if(c==' '){
            start++;
            return;
        }

        auto lookup = single_char_tokens.find(c);
        if(lookup != single_char_tokens.end()){
            emitToken(lookup->second);
        }else if(isNumber(c)){
            parseNumber();
        }else if(isEnglishLetter(c)){
            parseIdentifier();
        }else{
            error(std::string("Unrecognized symbol ") + c);
        }
    }

    void scan(){
        while(curr < size){
            processChar(source[curr]);
            curr++;
        }
    }

public:
    static std::vector<Token> getTokenStream(std::string source){
        Scanner scanner(source);
        scanner.scan();
        return scanner.token_stream;
    }
};

#endif // SCANNER_H
