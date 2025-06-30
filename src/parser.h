#pragma once
#include "node.h"
#include "token.h"

class Parser {
public:
    Parser()=default;
    Parser(vec<Token> toks);

    uptr<Node> parse();

private:
    void advance(TType expect);

    uptr<Node> parse_expr();
    uptr<Node> parse_cpd();

    uptr<Node> parse_int();
    uptr<Node> parse_str();
    uptr<Node> parse_id();

    uptr<Node> parse_var();
    vec<uptr<Node>> parse_fnargs();
    uptr<Node> parse_ret();

public:
    Token curtok() const {return m_toks[m_ind];}

private:
    vec<Token> m_toks;
    ll m_ind;
};
