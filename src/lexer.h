#pragma once
#include "token.h"
using ll=long long;

class Lexer {
    string m_prog;
    ll m_ind;
    ll m_line;

public:
    Lexer()=default;
    Lexer(const string &prog);

    vec<Token> tokenize();
    void advance();
    string collect_int();
    string collect_str();
    string collect_id();
};
