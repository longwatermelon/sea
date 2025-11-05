#include "lexer.h"
#include "util.h"
#include <cctype>
#include <stdexcept>

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
            string num = collect_int();
            // check for 'b' suffix for byte literals
            if (m_ind < sz(m_prog) && m_prog[m_ind] == 'b') {
                advance();
                // validate byte range (0-255)
                ll val = std::stoll(num);
                if (val < 0 || val > 255) {
                    throw std::runtime_error("Byte literal out of range (0-255): " + num);
                }
                tokens.push_back(Token(TType::BYTE_LIT, num, m_line));
            } else {
                tokens.push_back(Token(TType::INT, num, m_line));
            }
        } else if (std::isalpha(c) || c == '_') {
            tokens.push_back(Token(TType::ID, collect_id(), m_line));
        } else if (c == '"') {
            tokens.push_back(Token(TType::STR, collect_str(), m_line));
        } else if (c == '\'') {
            tokens.push_back(Token(TType::CHAR, collect_char(), m_line));
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
        } else if (c == ':') {
            tokens.push_back(Token(TType::COLON, ":", m_line));
            advance();
        } else if (c == ',') {
            tokens.push_back(Token(TType::COMMA, ",", m_line));
            advance();
        } else if (c == '[') {
            tokens.push_back(Token(TType::LBRACK, "[", m_line));
            advance();
        } else if (c == ']') {
            tokens.push_back(Token(TType::RBRACK, "]", m_line));
            advance();
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '%' || c == '|' || c == '&' || c == '!' || c == '<' || c == '>' || c == '.') {
            string op(1,c);
            // second character?
            if (m_ind+1 < sz(m_prog) && m_prog[m_ind+1]=='=') {
                op+='=';
                advance();
            } else if (m_ind+1 < sz(m_prog) && c=='|' && m_prog[m_ind+1]=='|') {
                op+='|';
                advance();
            } else if (m_ind+1 < sz(m_prog) && c=='&' && m_prog[m_ind+1]=='&') {
                op+='&';
                advance();
            } else if (m_ind+1 < sz(m_prog) && c=='-' && m_prog[m_ind+1]=='>') {
                op += '>';
                advance();
            }

            // potentially change type based on value
            if (op == "->") {
                tokens.push_back(Token(TType::ARROW, op, m_line));
            } else {
                tokens.push_back(Token(TType::OP, op, m_line));
            }
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

string Lexer::collect_char() {
    // skip opening quote
    advance();

    if (m_ind >= sz(m_prog)) {
        throw std::runtime_error("Unexpected end of file in character literal");
    }

    char ch = m_prog[m_ind];

    // handle escape sequences
    if (ch == '\\') {
        advance();
        if (m_ind >= sz(m_prog)) {
            throw std::runtime_error("Unexpected end of file in character literal");
        }
        char escape = m_prog[m_ind];
        switch (escape) {
            case 'n': ch = '\n'; break;
            case 't': ch = '\t'; break;
            case 'r': ch = '\r'; break;
            case '0': ch = '\0'; break;
            case '\\': ch = '\\'; break;
            case '\'': ch = '\''; break;
            default: ch = escape; break; // unrecognized escape, use literal
        }
    }

    advance();

    // check for closing quote
    if (m_ind >= sz(m_prog) || m_prog[m_ind] != '\'') {
        throw std::runtime_error("Expected closing quote in character literal");
    }
    advance();

    return std::to_string((int)(unsigned char)ch);
}
