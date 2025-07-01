#include "sea.h"

int main() {
    string out="prog";
    sea::compile(out+".c", out+".s");

    system(("as -64 "+out+".s -o "+out+".o").c_str());
    system(("ld "+out+".o -o "+out).c_str());

    return 0;
}
