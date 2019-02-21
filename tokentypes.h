#ifndef TOKENTYPES_H
#define TOKENTYPES_H

#include <unordered_map>

enum TokenType {
    ASTRISK,
    BACKSLASH,
    CAROT,
    COMMA,
    COS,
    e_CONSTANT,
    EXCLAMATION,
    EQUALS,
    FORWARDSLASH,
    LEFT_BRACE,
    LEFT_BRACKET,
    LEFT_PAREN,
    LOG10,
    MINUS,
    MODULUS,
    NATURAL_LOG,
    NEWLINE,
    NUMBER_LITERAL,
    PI,
    PLUS,
    RIGHT_BRACE,
    RIGHT_BRACKET,
    RIGHT_PAREN,
    SIN,
    TAN,
    UPRIGHTSLASH
};

const std::unordered_map<char, TokenType> single_char_tokens = {
    {'*', ASTRISK},
    {'/', BACKSLASH},
    {'^', CAROT},
    {',', COMMA},
    {'!', EXCLAMATION},
    {'=', EQUALS},
    {'\\', FORWARDSLASH},
    {'{', LEFT_BRACE},
    {'[', LEFT_BRACKET},
    {'(', LEFT_PAREN},
    {'-', MINUS},
    {'%', MODULUS},
    {'\n', NEWLINE},
    {'+', PLUS},
    {'}', RIGHT_BRACE},
    {']', RIGHT_BRACKET},
    {')', RIGHT_PAREN},
    {'|', UPRIGHTSLASH}
};

const std::unordered_map<std::string, TokenType> keywords = {
    {"cos", COS},
    {"e", e_CONSTANT},
    {"ln", NATURAL_LOG},
    {"log", LOG10},
    {"pi", PI},
    {"sin", SIN},
    {"tan", TAN}
};

#ifdef SCANNER_DEBUG
const std::string token_names[UPRIGHTSLASH+1] = {
    "ASTRISK",
    "BACKSLASH",
    "CAROT",
    "COMMA",
    "COS",
    "e_CONSTANT",
    "EXCLAMATION",
    "EQUALS",
    "FORWARDSLASH",
    "LEFT_BRACE",
    "LEFT_BRACKET",
    "LEFT_PAREN",
    "LOG10",
    "MINUS",
    "MODULUS",
    "NATURAL_LOG",
    "NEWLINE",
    "NUMBER_LITERAL",
    "PI",
    "PLUS",
    "RIGHT_BRACE",
    "RIGHT_BRACKET",
    "RIGHT_PAREN",
    "SIN",
    "TAN",
    "UPRIGHTSLASH"
};
#endif

#endif // TOKENTYPES_H
