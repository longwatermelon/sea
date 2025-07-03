#include "sea.h"
#include "args.h"
#include <fstream>
#include <algorithm>
#include <sstream>

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
        } else if (sz(nxt)==2 && nxt[0][0]=='-') {
            // flag w arg
            if (nxt[0]=="-o") {
                outfile = nxt[1];
            } else if (nxt[0]=="-b") {
                build_dir = nxt[1];
            }
        } else { // sz(nxt)==1, nxt[0][0]=='-'
            // flag wout arg
            if (nxt[0]=="--bundle") {
                bundle=true;
            }
        }

        nxt = args.next_arg();
    }

    // compiling
    system(("mkdir -p "+build_dir).c_str());
    vec<string> outfiles;
    string bundle_out;
    for (auto &in : infiles) {
        string out = in;
        std::replace(begin(out),end(out),'/','_');
        out = build_dir+"/"+out;
        outfiles.push_back(out);

        sea::compile(in,out+".s");

        if (bundle) {
            std::ifstream ifs(out+".s");
            std::stringstream ss;
            ss << ifs.rdbuf();
            bundle_out += ss.str();
            ifs.close();
        } else {
            system(("as -64 "+out+".s -o "+out+".o").c_str());
        }
    }

    string entry_asm = ".section .text\n"
                       "\t.global _start\n\n"
                       "_start:\n"
                       "\tcall main\n"
                       "\tmovq %rax, %rdi\n"
                       "\tmovq $60, %rax\n"
                       "\tsyscall\n\n";

    if (bundle) {
        // output asm to outfile, don't link
        std::ofstream ofs(outfile);
        ofs << entry_asm << bundle_out;
        ofs.close();
    } else {
        // create obj files, link
        std::ofstream ofs(build_dir+"/_sea_entry.c.s");
        ofs << entry_asm;
        ofs.close();
        system(("as -64 "+build_dir+"/_sea_entry.c.s -o "+build_dir+"/_sea_entry.c.o").c_str());
        outfiles.push_back(build_dir+"/_sea_entry.c");

        string link_cmd = "ld ";
        for (auto &out : outfiles) link_cmd += out+".o ";
        link_cmd += "-o "+outfile;
        system(link_cmd.c_str());
    }

    return 0;
}
