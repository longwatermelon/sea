#pragma once
#include "util.h"

struct Args {
    vec<string> args;
    int ind=0;

    Args(int argc, char **argv);
    vec<string> next_arg();
};
