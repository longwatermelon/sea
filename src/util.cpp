#include "util.h"
#include "token.h"
#include <optional>

string ttype2str(TType type) {
    switch(type) {
        case TType::ID: return "ID";
        case TType::LPAREN: return "(";
        case TType::RPAREN: return ")";
        case TType::LBRACE: return "{";
        case TType::RBRACE: return "}";
        case TType::SEMI: return ";";
        case TType::INT: return "INT";
        case TType::COMMA: return ",";
        case TType::OP: return "OP";
        default: return "UNKNOWN";
    }
}

std::optional<Arch> str2arch(const string &str) {
    if (str=="x86-64") return Arch::x86_64;
    if (str=="aarch64") return Arch::ARM64;
    return std::nullopt;
}
