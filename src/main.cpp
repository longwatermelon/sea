#include "sea.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.c>" << std::endl;
        return 1;
    }

    string input_file(argv[1]);
    string out = input_file;

    if (out.size() >= 2 && out.substr(out.size()-2) == ".c") {
        out = out.substr(0, out.size()-2);
    }

    sea::compile(input_file, out+".s");

    system(("as -64 "+out+".s -o "+out+".o").c_str());
    system(("ld "+out+".o -o "+out).c_str());

    return 0;
}
