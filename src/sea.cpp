#include "sea.h"
#include "asm.h"
#include "lexer.h"
#include "parser.h"
#include <sstream>
#include <fstream>

void sea::compile(const string &path, const string &out) {
    std::ifstream ifs(path);
    std::stringstream buf;
    buf << ifs.rdbuf();
    ifs.close();
    string prog = buf.str();

    Lexer lex(prog);
    vec<Token> toks = lex.tokenize();

    Parser p(toks);
    uptr<Node> root = p.parse();

    Visitor vis;
    string prog_asm = vis.gen(root);

    std::ofstream ofs(out);
    ofs << prog_asm;
    ofs.close();

    // system(("as -64 "+out+".s -o "+out+".o").c_str());
    // system(("ld "+out+".o -o "+out).c_str());
}
