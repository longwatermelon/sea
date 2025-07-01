#include "parser.h"
#include "errors.h"

Parser::Parser(vec<Token> toks) : m_toks(toks) {
    m_ind=0;
}

uptr<Node> Parser::parse() {
    m_toks.insert(begin(m_toks), Token(TType::LBRACE,"{"));
    m_toks.push_back(Token(TType::RBRACE, "}"));
    return parse_cpd();
}

void Parser::advance(TType expect) {
    if (curtok().type != expect) {
        errors::parser_unexpected_token(*this,expect);
    } else {
        m_ind++;
    }
}

uptr<Node> Parser::parse_expr() {
    switch (curtok().type) {
    // all useful
    case TType::ID: return parse_id();
    case TType::INT: return parse_int();
    case TType::STR: return parse_str();
    case TType::LBRACE: return parse_cpd();
    case TType::LPAREN: {
        advance(TType::LPAREN);
        uptr<Node> res = parse_expr();
        advance(TType::RPAREN);
        return res;
    }

    // all useless
    case TType::SEMI:
    case TType::RPAREN:
    case TType::RBRACE:
    case TType::COMMA:
        return nullptr;
    }
}

uptr<Node> Parser::parse_cpd() {
    // {
    advance(TType::LBRACE);

    // body
    uptr<Node> cpd = mkuq<Node>(NType::CPD);
    uptr<Node> expr = parse_expr();
    while (expr != nullptr) {
        cpd->cpd_nodes.push_back(std::move(expr));
        if (curtok().type == TType::SEMI) advance(TType::SEMI);
        expr = parse_expr();
    }

    // }
    advance(TType::RBRACE);
    return cpd;
}

uptr<Node> Parser::parse_int() {
    uptr<Node> val = mkuq<Node>(NType::VAL, DType::INT);
    val->val_int = std::stoi(curtok().val.c_str());
    advance(TType::INT);
    return val;
}

uptr<Node> Parser::parse_str() {
    uptr<Node> val = mkuq<Node>(NType::VAL, DType::STR);
    val->val_str = curtok().val;
    advance(TType::STR);
    return val;
}

uptr<Node> Parser::parse_id() {
    if (is_dtype(curtok().val)) {
        // data type -- prob declaration of something
        DType dtype = str2dtype(curtok().val);
        advance(TType::ID);

        uptr<Node> nxt = parse_expr();

        // check what's next?
        uptr<Node> res = mkuq<Node>(NType::DEF, dtype);
        if (nxt->type == NType::FN) {
            res->def_obj = std::move(nxt);
            res->def_as = parse_expr();
        } else if (nxt->type == NType::VAR) {
            res->def_obj = std::move(nxt);
            res->def_as = nullptr;
        }

        return res;
    } else {
        // not data type -- referencing something
        return parse_var();
    }
}

uptr<Node> Parser::parse_var() {
    string name = curtok().val;
    advance(TType::ID);

    // keywords
    if (name == "return") {
        return parse_ret();
    }

    // not keyword, reference to something code-defined
    uptr<Node> res;
    if (curtok().type == TType::LPAREN) {
        res = mkuq<Node>(NType::FN);
        res->fn_name = name;
        res->fn_args = parse_fnargs();
    } else {
        res = mkuq<Node>(NType::VAR);
        res->var_name = name;
    }

    return res;
}

vec<uptr<Node>> Parser::parse_fnargs() {
    // lparen
    advance(TType::LPAREN);

    // args
    vec<uptr<Node>> res;
    uptr<Node> expr = parse_expr();
    while (expr) {
        res.push_back(std::move(expr));
        if (curtok().type == TType::COMMA) advance(TType::COMMA);
        expr = parse_expr();
    }

    // rparen
    advance(TType::RPAREN);

    return res;
}

uptr<Node> Parser::parse_ret() {
    uptr<Node> res = mkuq<Node>(NType::RET);
    res->ret_val = parse_expr();
    return res;
}
