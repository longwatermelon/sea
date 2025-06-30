#pragma once
#include <string>
#include "util.h"

enum class TType {
    ID,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMI,
    INT,
    STR,
    COMMA,
};

struct Token {
    TType type;
    string val;

    Token()=default;
    Token(TType type, const string &val) : type(type), val(val) {}
};
