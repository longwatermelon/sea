#include "lexer.h"
#include "util.h"
#include <cctype>

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
            tokens.push_back(Token(TType::INT, collect_int(), m_line));
        } else if (std::isalpha(c) || c == '_') {
            tokens.push_back(Token(TType::ID, collect_id(), m_line));
        } else if (c == '"') {
            tokens.push_back(Token(TType::STR, collect_str(), m_line));
        } else if (c == '(') {
            tokens.push_back(Token(TType::LPAREN, "(", m_line));
            advance();
        } else if (c == ')') {
            tokens.push_back(Token(TType::RPAREN, ")", m_line));
            advance();
        } else if (c == '{') {
            tokens.push_back(Token(TType::LBRACE, "{", m_line));
            advance();
        } else if (c == '}') {
            tokens.push_back(Token(TType::RBRACE, "}", m_line));
            advance();
        } else if (c == ';') {
            tokens.push_back(Token(TType::SEMI, ";", m_line));
            advance();
        } else if (c == ',') {
            tokens.push_back(Token(TType::COMMA, ",", m_line));
            advance();
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '%' || c == '|' || c == '&' || c == '!') {
            string op(1,c);
            if (m_ind+1 < sz(m_prog) && m_prog[m_ind+1]=='=') {
                op+='=';
                advance();
            } else if (m_ind+1 < sz(m_prog) && c=='|' && m_prog[m_ind+1]=='|') {
                op+='|';
                advance();
            }
            tokens.push_back(Token(TType::OP, op, m_line));
            advance();
        } else if (c == '#') {
            tokens.push_back(Token(TType::HASH, "#", m_line));
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
