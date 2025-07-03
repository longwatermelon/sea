#include "sea.h"
#include "args.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    Args args(argc, argv);

    // parameters
    vec<string> infiles;
    string outfile="sea.out";
    bool bundle=false;
    string build_dir=".sea";

    // argparsing
    vec<string> nxt = args.next_arg();
    while (!empty(nxt)) {
        if (sz(nxt)==1 && nxt[0][0]!='-') {
            // path
            infiles.push_back(nxt[0]);
        } else if (sz(nxt)==1 && nxt[0][0]=='-') {
            // flag w arg
            if (nxt[0]=="-o") {
                outfile = nxt[1];
            } else if (nxt[0]=="-b") {
                build_dir = nxt[1];
            }
        } else { // sz(nxt)==2
            // flag wout arg
            if (nxt[0]=="--bundle") {
                bundle=true;
            }
        }

        nxt = args.next_arg();
    }

    // compiling
    system(("mkdir -p "+build_dir).c_str());
    for (auto &in : infiles) {
        sea::compile(in,in+".s");
        system(("as -64 "+in+".s -o "+in+".o").c_str());
    }

    string entry_asm = ".section .text\n"
                       "\t.global _start\n\n"
                       "_start:\n"
                       "\tcall main\n"
                       "\tmovq %rax, %rdi\n"
                       "\tmovq $60, %rax\n"
                       "\tsyscall\n\n";
    std::ofstream ofs(build_dir+"/_sea_entry.c.s");
    ofs << entry_asm;
    ofs.close();
    system(("as -64 "+build_dir+"/_sea_entry.c.s -o "+build_dir+"/_sea_entry.c.o").c_str());
    infiles.push_back(build_dir+"/_sea_entry.c");

    string link_cmd = "ld ";
    for (auto &in : infiles) link_cmd += in+".o ";
    link_cmd += "-o "+outfile;
    system(link_cmd.c_str());

    return 0;
}
