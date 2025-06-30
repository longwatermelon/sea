#include "errors.h"

void errors::parser_unexpected_token(Parser &p, TType expect) {
    // TODO better error
    printf("[parser.cpp] ERROR: unexpected token '%s'.\n", p.curtok().val.c_str());
    exit(1);
}
