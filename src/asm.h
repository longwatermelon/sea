#pragma once
#include "node.h"

class Visitor {
public:
    Visitor()=default;

    string gen(uptr<Node> &root);
    void gen_expr(uptr<Node> &expr);

    void gen_cpd(uptr<Node> &cpd);
    void gen_fdef(uptr<Node> &fdef);
    void gen_ret(uptr<Node> &ret);

    // sets node->_addr
    void gen_stack_push(uptr<Node> &node);

    int addrof(uptr<Node> &node);

private:
    string m_asm;
    int m_rsp=0; // stack ptr
};
