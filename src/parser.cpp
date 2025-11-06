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
    case TType::STR: return parse_str();
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
            uptr<Node> cur = mkuq<Node>(NType::BINOP);
            cur->op_type = ".";
            cur->op_l = std::move(left);
            advance(TType::OP);
            cur->op_r = mkuq<Node>(NType::VAR);
            cur->op_r->var_name = curtok().val;
            advance(TType::ID);
            left = std::move(cur);
            continue;
        }
        if (curtok().type == TType::LBRACK) {
            uptr<Node> res = mkuq<Node>(NType::UNOP);
            res->unop_type = "*";

            res->unop_obj = mkuq<Node>(NType::BINOP);
            res->unop_obj->op_type = "+";
            res->unop_obj->op_l = std::move(left);
            advance(TType::LBRACK);
            res->unop_obj->op_r = parse_expr();
            advance(TType::RBRACK);

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

        uptr<Node> cur = mkuq<Node>(NType::BINOP);
        cur->op_l = std::move(left);
        cur->op_r = std::move(right);
        cur->op_type = op;
        left = std::move(cur);
    }

    return left;
}

uptr<Node> Parser::parse_cpd() {
    // {
    advance(TType::LBRACE);

    // body
    uptr<Node> cpd = mkuq<Node>(NType::CPD);
    uptr<Node> expr = parse_expr();
    while (expr != nullptr) {
        cpd->cpd_nodes.push_back(std::move(expr));
        if (m_ind>0 && m_toks[m_ind-1].val != "}") advance(TType::SEMI);
        expr = parse_expr();
    }

    // }
    advance(TType::RBRACE);
    return cpd;
}

uptr<Node> Parser::parse_int() {
    uptr<Node> val = mkuq<Node>(NType::VAL);
    val->val_int = std::stoll(curtok().val.c_str());
    val->val_dtype = DType(DTypeBase::INT);
    advance(TType::INT);
    return val;
}

uptr<Node> Parser::parse_char() {
    uptr<Node> val = mkuq<Node>(NType::VAL);
    val->val_byte = (unsigned char)std::stoi(curtok().val.c_str());
    val->val_dtype = DType(DTypeBase::BYTE);
    advance(TType::CHAR);
    return val;
}

uptr<Node> Parser::parse_byte() {
    uptr<Node> val = mkuq<Node>(NType::VAL);
    val->val_byte = (unsigned char)std::stoi(curtok().val.c_str());
    val->val_dtype = DType(DTypeBase::BYTE);
    advance(TType::BYTE_LIT);
    return val;
}

uptr<Node> Parser::parse_str() {
    uptr<Node> val = mkuq<Node>(NType::STR);
    val->str_val = curtok().val;
    val->str_id = m_label_id;
    // TODO val_dtype
    m_label_id++;
    advance(TType::STR);
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
    } else if (name == "fn") {
        return parse_fdef();
    } else if (name == "let") {
        // expect parse name:type = expr, BINOP
        return parse_expr();
    } else if (name == "break") {
        return mkuq<Node>(NType::BREAK);
    } else if (name == "continue") {
        return mkuq<Node>(NType::CONT);
    } else if (name == "struct") {
        return parse_sdef();
    }

    // must be reference to some program-defined symbol at this point
    uptr<Node> res;
    if (curtok().type == TType::LPAREN) {
        // function call
        res = mkuq<Node>(NType::FCALL);
        res->fcall_name = name;

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
        res->fcall_args = std::move(args);
    } else {
        // variable
        res = mkuq<Node>(NType::VAR);
        res->var_name = name;

        if (curtok().type == TType::COLON) {
            advance(TType::COLON);
            res = mkuq<Node>(NType::TYPEVAR);
            res->typevar_name = name;
            res->typevar_dtype = parse_dtype()->dtype_type;
        }
    }

    return res;
}

uptr<Node> Parser::parse_dtype() {
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

    uptr<Node> res = mkuq<Node>(NType::DTYPE);
    res->dtype_type = dtype;
    return res;
}

uptr<Node> Parser::parse_fdef() {
    uptr<Node> fdef = mkuq<Node>(NType::FDEF);

    // name
    fdef->fdef_name = curtok().val;
    advance(TType::ID);

    // params
    advance(TType::LPAREN);
    while (curtok().type != TType::RPAREN) {
        fdef->fdef_params.push_back(parse_typevar());

        if (curtok().type == TType::COMMA) advance(TType::COMMA);
        else break;
    }
    advance(TType::RPAREN);

    // return type
    advance(TType::ARROW);
    fdef->fdef_ret_dtype = parse_dtype()->dtype_type;

    // body
    fdef->fdef_body = parse_expr();

    return fdef;
}

uptr<Node> Parser::parse_ret() {
    uptr<Node> res = mkuq<Node>(NType::RET);
    res->ret_val = parse_expr();
    return res;
}

uptr<Node> Parser::parse_typevar() {
    uptr<Node> var = mkuq<Node>(NType::TYPEVAR);
    var->typevar_name = curtok().val;
    advance(TType::ID);
    advance(TType::COLON);
    var->typevar_dtype = parse_dtype()->dtype_type;
    return var;
}

uptr<Node> Parser::parse_if() {
    uptr<Node> res = mkuq<Node>(NType::IF);
    res->if_id = m_label_id;
    m_label_id++;

    // cond
    advance(TType::LPAREN);
    res->if_cond = parse_expr();
    advance(TType::RPAREN);

    // body
    res->if_body = parse_expr();

    // else block
    if (curtok().type == TType::ID && curtok().val == "else") {
        advance(TType::ID);
        res->if_else = parse_expr();
    }

    return res;
}

uptr<Node> Parser::parse_while() {
    uptr<Node> res = mkuq<Node>(NType::WHILE);
    res->while_id = m_label_id;
    m_label_id++;

    // cond
    advance(TType::LPAREN);
    res->while_cond = parse_expr();
    advance(TType::RPAREN);

    // body
    res->while_body = parse_expr();

    return res;
}

uptr<Node> Parser::parse_unop() {
    uptr<Node> res = mkuq<Node>(NType::UNOP);
    res->unop_type = curtok().val;
    advance(TType::OP);
    // some high precedence to give unops higher prec than binops
    res->unop_obj = parse_expr(100);

    return res;
}

uptr<Node> Parser::parse_sdef() {
    uptr<Node> sdef = mkuq<Node>(NType::SDEF);

    sdef->sdef_name = curtok().val;
    advance(TType::ID);
    advance(TType::LBRACE);
    while (curtok().type != TType::RBRACE) {
        uptr<Node> typevar = parse_typevar();
        sdef->sdef_membs.push_back(std::move(typevar));
        if (curtok().type == TType::COMMA) advance(TType::COMMA);
        else break;
    }
    advance(TType::RBRACE);

    m_sdefs.push_back(sdef.get());
    return sdef;
}
