#include "asm.h"

Visitor::Visitor(uptr<Node> &root) {
    // TODO: Implement constructor
}

void Visitor::gen_expr(uptr<Node> &expr) {
    // TODO: Implement expression generation
}

void Visitor::gen_cpd(uptr<Node> &cpd) {
    // TODO: Implement compound statement generation
}

void Visitor::gen_fdef(uptr<Node> &fdef) {
    // TODO: Implement function definition generation
}

void Visitor::gen_ret(uptr<Node> &ret) {
    // TODO: Implement return statement generation
}
