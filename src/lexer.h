#pragma once
#include "token.h"
#include <vector>
using ll=long long;

struct Lexer {
    std::string m_prog;
    ll m_ind;
    ll m_line;

    Lexer()=default;
    Lexer(const std::string &prog);

    std::vector<Token> tokenize();
    void advance();
    std::string collect_int();
    std::string collect_str();
    std::string collect_id();
};
