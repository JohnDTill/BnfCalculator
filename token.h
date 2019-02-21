#ifndef TOKEN_H
#define TOKEN_H

#include "tokentypes.h"

struct Token{
    TokenType type;
    unsigned long long start;
    unsigned long long size;
    unsigned long long line;
};

#ifdef SCANNER_DEBUG
inline std::string toString(Token t, std::string& source){
    TokenType type = t.type;
    std::string name = token_names[type];
    if(type==NUMBER_LITERAL){
        return name + ": " + source.substr(t.start, t.size);
    }else{
        return name;
    }
}

#endif

#endif // TOKEN_H
