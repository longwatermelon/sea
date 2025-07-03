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

    uptr<Node> parse_atom();
    uptr<Node> parse_expr(int mn_prec=0);
    uptr<Node> parse_cpd();

    uptr<Node> parse_int();
    uptr<Node> parse_str();
    uptr<Node> parse_id();

    uptr<Node> parse_var();
    vec<uptr<Node>> parse_fnargs();
    uptr<Node> parse_ret();

    uptr<Node> parse_if();
    uptr<Node> parse_while();

    uptr<Node> parse_unop();

public:
    Token curtok() const {return m_toks[m_ind];}

private:
    vec<Token> m_toks;
    ll m_ind;

    static ll m_label_id;
};
