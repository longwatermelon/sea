#include "util.h"
#include "token.h"
#include "node.h"

string ttype2str(TType type) {
    switch(type) {
        case TType::ID: return "ID";
        case TType::LPAREN: return "(";
        case TType::RPAREN: return ")";
        case TType::LBRACE: return "{";
        case TType::RBRACE: return "}";
        case TType::SEMI: return ";";
        case TType::INT: return "INT";
        case TType::STR: return "STR";
        case TType::COMMA: return ",";
        case TType::OP: return "OP";
        default: return "UNKNOWN";
    }
}

string ntype2str(NType type) {
    switch(type) {
        case NType::CPD: return "CPD";
        case NType::VAL: return "VAL";
        case NType::DEF: return "DEF";
        case NType::FN: return "FN";
        case NType::VAR: return "VAR";
        case NType::RET: return "RET";
        case NType::BINOP: return "BINOP";
        case NType::IF: return "IF";
        default: return "UNKNOWN";
    }
}
