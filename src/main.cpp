#include "parser.h"
#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("./prog.c");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open ./prog.c" << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    string program = buffer.str();
    
    Lexer lexer(program);
    vec<Token> tokens = lexer.tokenize();
    
    Parser parser(tokens);
    uptr<Node> ast = parser.parse();
    
    return 0;
}
