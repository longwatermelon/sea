#include "parser.h"
#include "errors.h"
#include <cassert>

ll Parser::m_label_id=0;

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

uptr<Node> Parser::parse_atom() {
    switch (curtok().type) {
    // all useful
    case TType::ID: return parse_id();
    case TType::INT: return parse_int();
    case TType::CHAR: return parse_char();
    case TType::BYTE_LIT: return parse_byte();
    case TType::LBRACE: return parse_cpd();
    case TType::LPAREN: {
        advance(TType::LPAREN);
        uptr<Node> res = parse_expr();
        advance(TType::RPAREN);
        return res;
    }
    case TType::OP: return parse_unop();

    // all useless
    case TType::SEMI:
    case TType::RPAREN:
    case TType::RBRACE:
    case TType::COMMA:
    case TType::ARROW:
    case TType::COLON:
    case TType::RBRACK:
    case TType::LBRACK:
        break;
    }

    return nullptr;
}

uptr<Node> Parser::parse_expr(int mn_prec) {
    uptr<Node> left = parse_atom();

    // if ending off compound -- the only type that doesn't need a semicolon
    // this means ops should treat it as if a semicolon was placed after the cpd
    if (m_ind>0 && m_toks[m_ind-1].val == "}") {
        return left;
    }

    // handle . and [] repeatedly (a[b].c[d].e[f])
    while (true) {
        if (curtok().type == TType::OP && curtok().val == ".") {
            auto cur = mkuq<BinopNode>();
            cur->type = ".";

            cur->l = std::move(left);
            auto r = mkuq<VarNode>();
            advance(TType::OP);
            r->name = curtok().val;
            cur->r = std::move(r);
            advance(TType::ID);

            left = std::move(cur);
            continue;
        }
        if (curtok().type == TType::LBRACK) {
            auto res = mkuq<UnopNode>();
            res->type = "*";

            auto obj = mkuq<BinopNode>();
            obj->type = "+";
            obj->l = std::move(left);
            advance(TType::LBRACK);
            obj->r = parse_expr();
            advance(TType::RBRACK);
            res->obj = std::move(obj);

            left = std::move(res);
            continue;
        }

        break;
    }

    // binops
    while (curtok().type == TType::OP) {
        string op = curtok().val;
        int prec = precedence(op);
        if (prec < mn_prec) break;

        advance(curtok().type);
        uptr<Node> right = parse_expr(prec+1);

        auto cur = mkuq<BinopNode>();
        cur->l = std::move(left);
        cur->r = std::move(right);
        cur->type = op;
        left = std::move(cur);
    }

    return left;
}

uptr<CpdNode> Parser::parse_cpd() {
    // {
    advance(TType::LBRACE);

    // body
    auto cpd = mkuq<CpdNode>();
    uptr<Node> expr = parse_expr();
    while (expr != nullptr) {
        cpd->nodes.push_back(std::move(expr));
        if (m_ind>0 && m_toks[m_ind-1].val != "}") advance(TType::SEMI);
        expr = parse_expr();
    }

    // }
    advance(TType::RBRACE);
    return cpd;
}

uptr<ValIntNode> Parser::parse_int() {
    auto val = mkuq<ValIntNode>();
    val->value = std::stoll(curtok().val.c_str());
    advance(TType::INT);
    return val;
}

uptr<ValByteNode> Parser::parse_char() {
    auto val = mkuq<ValByteNode>();
    val->value = (unsigned char)std::stoi(curtok().val.c_str());
    advance(TType::CHAR);
    return val;
}

uptr<ValByteNode> Parser::parse_byte() {
    auto val = mkuq<ValByteNode>();
    val->value = (unsigned char)std::stoi(curtok().val.c_str());
    advance(TType::BYTE_LIT);
    return val;
}

uptr<Node> Parser::parse_id() {
    string name = curtok().val;

    // type
    if (is_dtypebase(name, m_sdefs)) {
        return parse_dtype();
    }

    advance(TType::ID);

    // keywords
    if (name == "return") {
        return parse_ret();
    } else if (name == "if") {
        return parse_if();
    } else if (name == "while") {
        return parse_while();
    } else if (name == "for") {
        return parse_for();
    } else if (name == "fn") {
        return parse_fdef();
    } else if (name == "let") {
        // expect parse name:type = expr, BINOP
        return parse_expr();
    } else if (name == "break") {
        return mkuq<BreakNode>();
    } else if (name == "continue") {
        return mkuq<ContinueNode>();
    } else if (name == "struct") {
        return parse_sdef();
    }

    // must be reference to some program-defined symbol at this point
    uptr<Node> res;
    if (curtok().type == TType::LPAREN) {
        // function call
        auto fcall = mkuq<FcallNode>();
        fcall->name = name;

        // args
        advance(TType::LPAREN);
        vec<uptr<Node>> args;
        uptr<Node> expr = parse_expr();
        while (expr) {
            args.push_back(std::move(expr));
            if (curtok().type == TType::COMMA) advance(TType::COMMA);
            expr = parse_expr();
        }
        advance(TType::RPAREN);
        fcall->args = std::move(args);

        res = std::move(fcall);
    } else {
        // variable
        auto var = mkuq<VarNode>();
        var->name = name;

        if (curtok().type == TType::COLON) {
            advance(TType::COLON);
            auto typevar = mkuq<TypevarNode>();
            typevar->name = name;
            typevar->dtype = parse_dtype()->dtype;
            res = std::move(typevar);
        } else {
            res = std::move(var);
        }
    }

    return res;
}

uptr<DtypeNode> Parser::parse_dtype() {
    // TODO generics
    DType dtype;
    dtype.base = str2dtypebase(curtok().val, m_sdefs);
    if (dtype.base == DTypeBase::STRUCT) {
        dtype.struct_name = curtok().val;
    }
    advance(TType::ID);

    while (curtok().type == TType::OP && curtok().val == "*") {
        dtype.ptrcnt++;
        advance(TType::OP);
    }

    auto res = mkuq<DtypeNode>();
    res->dtype = dtype;
    return res;
}

uptr<FdefNode> Parser::parse_fdef() {
    auto fdef = mkuq<FdefNode>();

    // name
    fdef->name = curtok().val;
    advance(TType::ID);

    // params
    advance(TType::LPAREN);
    while (curtok().type != TType::RPAREN) {
        fdef->params.push_back(parse_typevar());

        if (curtok().type == TType::COMMA) advance(TType::COMMA);
        else break;
    }
    advance(TType::RPAREN);

    // return type
    advance(TType::ARROW);
    fdef->ret_dtype = parse_dtype()->dtype;

    // body
    fdef->body = parse_expr();

    return fdef;
}

uptr<RetNode> Parser::parse_ret() {
    auto res = mkuq<RetNode>();
    res->expr = parse_expr();
    return res;
}

uptr<TypevarNode> Parser::parse_typevar() {
    auto var = mkuq<TypevarNode>();
    var->name = curtok().val;
    advance(TType::ID);
    advance(TType::COLON);
    var->dtype = parse_dtype()->dtype;
    return var;
}

uptr<IfNode> Parser::parse_if() {
    auto res = mkuq<IfNode>();
    res->id = m_label_id;
    m_label_id++;

    // cond
    advance(TType::LPAREN);
    res->cond = parse_expr();
    advance(TType::RPAREN);

    // body
    res->body = parse_expr();

    // else block
    if (curtok().type == TType::ID && curtok().val == "else") {
        advance(TType::ID);
        res->else_ = parse_expr();
    }

    return res;
}

uptr<WhileNode> Parser::parse_while() {
    auto res = mkuq<WhileNode>();
    res->id = m_label_id;
    m_label_id++;

    // cond
    advance(TType::LPAREN);
    res->cond = parse_expr();
    advance(TType::RPAREN);

    // body
    res->body = parse_expr();

    return res;
}

uptr<ForNode> Parser::parse_for() {
    auto res = mkuq<ForNode>();
    res->id = m_label_id;
    m_label_id++;

    // init
    advance(TType::LPAREN);
    res->init = parse_expr();
    advance(TType::SEMI);

    // cond
    res->cond = parse_expr();
    advance(TType::SEMI);

    // upd
    res->upd = parse_expr();
    advance(TType::RPAREN);

    // body
    res->body = parse_expr();

    return res;
}

uptr<UnopNode> Parser::parse_unop() {
    auto res = mkuq<UnopNode>();
    res->type = curtok().val;
    advance(TType::OP);
    // some high precedence to give unops higher prec than binops
    res->obj = parse_expr(100);

    return res;
}

uptr<SdefNode> Parser::parse_sdef() {
    auto sdef = mkuq<SdefNode>();
    m_sdefs.push_back(sdef.get());

    sdef->name = curtok().val;
    advance(TType::ID);
    advance(TType::LBRACE);
    while (curtok().type != TType::RBRACE) {
        auto typevar = parse_typevar();
        sdef->membs.push_back(std::move(typevar));
        if (curtok().type == TType::COMMA) advance(TType::COMMA);
        else break;
    }
    advance(TType::RBRACE);

    return sdef;
}
