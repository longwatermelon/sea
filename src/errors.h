#pragma once
#include "parser.h"

namespace errors {
    void parser_unexpected_token(Parser &p, TType expect);
}
