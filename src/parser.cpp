#include "parser.h"
#include "errors.h"

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
        break;
    }

    return nullptr;
}

uptr<Node> Parser::parse_expr(int mn_prec) {
    uptr<Node> left = parse_atom();

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
    uptr<Node> val = mkuq<Node>(NType::VAL, DType::INT);
    val->val_int = std::stoi(curtok().val.c_str());
    advance(TType::INT);
    return val;
}

uptr<Node> Parser::parse_str() {
    uptr<Node> val = mkuq<Node>(NType::STR);
    val->str_val = curtok().val;
    val->str_id = m_label_id;
    m_label_id++;
    advance(TType::STR);
    return val;
}

uptr<Node> Parser::parse_id() {
    if (is_dtype(curtok().val)) {
        // data type -- prob declaration of something
        string dtype_name = curtok().val;
        DType dtype = str2dtype(dtype_name);
        advance(TType::ID);

        uptr<Node> nxt = parse_expr();

        // just datatype on its own?
        if (!nxt) {
            uptr<Node> res = mkuq<Node>(NType::VAR);
            res->var_name = dtype_name;
            return res;
        }

        // check what's next
        uptr<Node> res = mkuq<Node>(NType::DEF, dtype);
        if (nxt->type == NType::FN) {
            res->def_obj = std::move(nxt);
        } else if (nxt->type == NType::VAR) {
            res->def_obj = std::move(nxt);
        } else if (nxt->type == NType::BINOP && nxt->op_type == "=") {
            res->def_obj = std::move(nxt);
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
    } else if (name == "if") {
        return parse_if();
    } else if (name == "while") {
        return parse_while();
    }

    // not keyword, reference to something code-defined
    uptr<Node> res;
    if (curtok().type == TType::LPAREN) {
        res = mkuq<Node>(NType::FN);
        res->fn_name = name;
        res->fn_args = parse_fnargs();

        if (curtok().type == TType::LBRACE) {
            res->fn_body = parse_expr();
        }
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
