#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string token_type_to_string(TType type) {
    switch (type) {
        case TType::ID: return "ID";
        case TType::LPAREN: return "LPAREN";
        case TType::RPAREN: return "RPAREN";
        case TType::LBRACE: return "LBRACE";
        case TType::RBRACE: return "RBRACE";
        case TType::SEMI: return "SEMI";
        case TType::EOF_: return "EOF";
        case TType::INT: return "INT";
        case TType::STR: return "STR";
        default: return "UNKNOWN";
    }
}

int main() {
    std::ifstream file("./prog.c");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open ./prog.c" << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();
    
    Lexer lexer(content);
    std::vector<Token> tokens = lexer.tokenize();
    
    std::cout << "Tokens from ./prog.c:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << token_type_to_string(token.type) << ": \"" << token.val << "\"" << std::endl;
    }
    
    return 0;
}
