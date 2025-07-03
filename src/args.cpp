#include "args.h"
#include <sstream>

Args::Args(int argc, char **argv) {
    for (int i=1; i<argc; ++i) {
        args.push_back(argv[i]);
    }
}

vec<string> Args::next_arg() {
    if (ind>=sz(args)) return {};

    vec<string> res;
    std::stringstream ss(args[ind]);
    string buf;
    ss>>buf;
    res.push_back(buf);

    if (args[ind][0]=='-') {
        // --
        if (sz(args[ind])>=2 && args[ind][1]=='-') {
            ind++;
            return res;
        }

        // -
        ind++;
        string arg;
        ss>>arg;
        res.push_back(arg);
    } else {
        // path
        ind++;
    }

    return res;
}
