#pragma once
#include <string>

enum class TType {
    ID,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMI,
    INT,
    STR,
    EOF_,
};

struct Token {
    TType type;
    std::string val;

    Token()=default;
    Token(TType type, const std::string &val) : type(type), val(val) {}
};
