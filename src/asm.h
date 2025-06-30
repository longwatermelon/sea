#pragma once
#include "node.h"

class Visitor {
public:
    Visitor()=default;
    Visitor(uptr<Node> &root);

    void gen_expr(uptr<Node> &expr);

    void gen_cpd(uptr<Node> &cpd);
    void gen_fdef(uptr<Node> &fdef);
    void gen_ret(uptr<Node> &ret);

private:
    string m_out;
};
