#include "args.h"

Args::Args(int argc, char **argv) {
    for (int i=1; i<argc; ++i) {
        args.push_back(argv[i]);
    }
}

vec<string> Args::next_arg() {
    if (ind>=sz(args)) return {};

    vec<string> res;
    if (args[ind][0]=='-' && (sz(args[ind])<2 || args[ind][1]!='-')) {
        res.push_back(args[ind]);
        ind++;
    }

    res.push_back(args[ind]);
    ind++;

    return res;
}
