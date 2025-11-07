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
    uptr<CpdNode> parse_cpd();

    uptr<ValIntNode> parse_int();
    uptr<ValByteNode> parse_char();
    uptr<ValByteNode> parse_byte();
    uptr<Node> parse_id();
    uptr<DtypeNode> parse_dtype();

    uptr<BinopNode> parse_vardef();
    uptr<FdefNode> parse_fdef();
    uptr<RetNode> parse_ret();
    uptr<TypevarNode> parse_typevar();

    uptr<IfNode> parse_if();
    uptr<WhileNode> parse_while();

    uptr<UnopNode> parse_unop();

    uptr<SdefNode> parse_sdef();

public:
    Token curtok() const {return m_toks[m_ind];}

private:
    vec<Token> m_toks;
    ll m_ind;

    static ll m_label_id;

    vec<SdefNode*> m_sdefs;
};
