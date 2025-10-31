#include "sea.h"
#include "args.h"
#include "util.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
    Args args(argc, argv);

    // parameters
    vec<string> infiles;
    string outfile="sea.out";
    bool bundle=false;
    bool no_entry=false;
    string build_dir=".sea";
    std::optional<Arch> arch_override;

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
            } else if (nxt[0]=="-arch") {
                arch_override = str2arch(nxt[1]);
                if (!arch_override.has_value()) {
                    std::cerr << "error: invalid architecture '" << nxt[1] << "'\n";
                    std::cerr << "valid options: x86-64, aarch64\n";
                    return 1;
                }
            }
        } else { // sz(nxt)==1, nxt[0][0]=='-'
            // flag wout arg
            if (nxt[0]=="--bundle") {
                bundle=true;
            } else if (nxt[0]=="--no-entry") {
                no_entry=true;
            }
        }

        nxt = args.next_arg();
    }

    Arch arch;
    if (arch_override.has_value()) {
        arch = arch_override.value();
    } else {
#ifdef __APPLE__
        arch=Arch::ARM64;
#elif defined(__linux__)
        arch=Arch::x86_64;
#endif
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

        sea::compile(in, out+".s", arch);

        if (bundle) {
            std::ifstream ifs(out+".s");
            std::stringstream ss;
            ss << ifs.rdbuf();
            bundle_out += ss.str();
            ifs.close();
        } else {
            switch (arch) {
            case Arch::x86_64: system(("as --64 "+out+".s -o "+out+".o").c_str()); break;
            case Arch::ARM64: system(("as "+out+".s -o "+out+".o").c_str()); break;
            }
        }
    }

    string entry_asm; 
    switch (arch) {
    case Arch::x86_64: entry_asm = ".section .text\n"
                                   "\t.global _start\n\n"
                                   "_start:\n"
                                   "\tcall main\n"
                                   "\tmovq %rax, %rdi\n"
                                   "\tmovq $60, %rax\n"
                                   "\tsyscall\n\n"; break;
    case Arch::ARM64: entry_asm = ".text\n"
                                  "\t.global _start\n\n"
                                  "_start:\n"
                                  "\tbl _main\n"
                                  "\tmov x8, #93\n"
                                  "\tsvc #0\n\n"; break;
    }

    if (bundle) {
        // output asm to outfile, don't link
        std::ofstream ofs(outfile);
        if (!no_entry) ofs << entry_asm;
        ofs << bundle_out;
        ofs.close();
    } else {
        // create obj files, link
        if (!no_entry) {
            std::ofstream ofs(build_dir+"/_sea_entry.c.s");
            ofs << entry_asm;
            ofs.close();
            switch (arch) {
            case Arch::x86_64: system(("as --64 "+build_dir+"/_sea_entry.c.s -o "+build_dir+"/_sea_entry.c.o").c_str()); break;
            case Arch::ARM64: system(("as "+build_dir+"/_sea_entry.c.s -o "+build_dir+"/_sea_entry.c.o").c_str()); break;
            }
            outfiles.push_back(build_dir+"/_sea_entry.c");
        }

        string link_cmd;
        switch (arch) {
        case Arch::x86_64: 
            link_cmd = "ld ";
            for (auto &out : outfiles) link_cmd += out+".o ";
            link_cmd += "-o "+outfile;
            break;
        case Arch::ARM64:
            link_cmd = "clang ";
            for (auto &out : outfiles) link_cmd += out+".o ";
            link_cmd += "-o "+outfile;
            break;
        }
        system(link_cmd.c_str());
    }

    return 0;
}
