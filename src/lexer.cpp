#include "lexer.h"
#include "util.h"
#include <cctype>
// TODO include line info in tokens

Lexer::Lexer(const string &prog) : m_prog(prog) {
    m_ind=0;
    m_line=1;
}

vec<Token> Lexer::tokenize() {
    vec<Token> tokens;
    
    while (m_ind < sz(m_prog)) {
        char c = m_prog[m_ind];

        if (std::isspace(c)) {
            if (c=='\n') m_line++;
            advance();
            continue;
        }

        if (std::isdigit(c)) {
            tokens.push_back(Token(TType::INT, collect_int()));
        } else if (std::isalpha(c) || c == '_') {
            tokens.push_back(Token(TType::ID, collect_id()));
        } else if (c == '"') {
            tokens.push_back(Token(TType::STR, collect_str()));
        } else if (c == '(') {
            tokens.push_back(Token(TType::LPAREN, "("));
            advance();
        } else if (c == ')') {
            tokens.push_back(Token(TType::RPAREN, ")"));
            advance();
        } else if (c == '{') {
            tokens.push_back(Token(TType::LBRACE, "{"));
            advance();
        } else if (c == '}') {
            tokens.push_back(Token(TType::RBRACE, "}"));
            advance();
        } else if (c == ';') {
            tokens.push_back(Token(TType::SEMI, ";"));
            advance();
        } else if (c == ',') {
            tokens.push_back(Token(TType::COMMA, ","));
            advance();
        } else {
            advance();
        }
    }

    return tokens;
}

void Lexer::advance() {
    if (m_ind < sz(m_prog)) {
        m_ind++;
    }
}

string Lexer::collect_int() {
    string result;
    while (m_ind < sz(m_prog) && std::isdigit(m_prog[m_ind])) {
        result += m_prog[m_ind];
        advance();
    }
    return result;
}

string Lexer::collect_str() {
    string result;
    // opening quote
    advance();

    // string contents
    while (m_ind < sz(m_prog) && m_prog[m_ind] != '"') {
        result += m_prog[m_ind];
        advance();
    }

    // closing quote
    if (m_ind < sz(m_prog)) advance();
    return result;
}

string Lexer::collect_id() {
    string result;
    while (m_ind < sz(m_prog) && (std::isalnum(m_prog[m_ind]) || m_prog[m_ind] == '_')) {
        result += m_prog[m_ind];
        advance();
    }
    return result;
}
