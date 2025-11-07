#pragma once
#include "util.h"

enum class TType {
    ID,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACK,
    RBRACK,
    SEMI,
    INT,
    CHAR,
    BYTE_LIT,
    COMMA,
    OP,
    ARROW,
    COLON,
};

struct Token {
    TType type;
    string val;
    ll line;

    Token()=default;
    Token(TType type, const string &val, ll line = 1) : type(type), val(val), line(line) {}
};
