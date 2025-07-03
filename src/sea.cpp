#include "sea.h"
#include "asm.h"
#include "lexer.h"
#include "parser.h"
#include "preprocessor.h"
#include <sstream>
#include <fstream>
#include <filesystem>

void sea::compile(const string &path, const string &out) {
    std::ifstream ifs(path);
    std::stringstream buf;
    buf << ifs.rdbuf();
    ifs.close();
    string prog = buf.str();

    string base_dir = std::filesystem::path(path).parent_path();
    prog = preprocess(prog, base_dir);

    Lexer lex(prog);
    vec<Token> toks = lex.tokenize();

    Parser p(toks);
    uptr<Node> root = p.parse();

    Visitor vis;
    string prog_asm = vis.gen(root);

    std::ofstream ofs(out);
    ofs << prog_asm;
    ofs.close();
}
