#include "sea.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.c>" << std::endl;
        return 1;
    }

    vec<string> objs;
    for (int i=1; i<argc; ++i) {
        string path(argv[1]);

        string out = path;
        if (sz(out)>=2 && out.substr(sz(out)-2) == ".c") {
            out = out.substr(0, sz(out)-2);
        }

        sea::compile(path, out+".s");

        system(("as -64 "+out+".s -o "+out+".o").c_str());
        objs.push_back(out+".o");
    }

    string link_cmd = "ld ";
    for (auto &obj : objs) link_cmd += obj+' ';
    link_cmd += "-o sea.out";
    system(link_cmd.c_str());

    return 0;
}
