#include "errors.h"
#include "util.h"

#define RESET "\x1b[0m"
#define RED_BOLD "\x1b[1;31m"
#define YELLOW_BOLD "\x1b[1;33m"
#define WHITE_BOLD "\x1b[1;37m"
#define MAGENTA_BOLD "\x1b[1;35m"

#define ERROR RED_BOLD "ERROR: " RESET
#define INTERNAL_ERROR RED_BOLD "INTERNAL ERROR: " RESET
#define WARNING YELLOW_BOLD "WARNING: " RESET
#define WARNING_FLAG(x) "[" MAGENTA_BOLD x RESET "]"

#define ERROR_RANGE 1

void errors::parser_unexpected_token(Parser &p, TType expect) {
    printf(
        ERROR "unexpected token '%s', expected '%s' token.\n",
        p.curtok().val.c_str(), ttype2str(expect).c_str()
    );
    exit(EXIT_FAILURE);
}
