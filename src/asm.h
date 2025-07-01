#pragma once
#include "node.h"
#include "scope.h"

class Visitor {
public:
    Visitor()=default;

    string gen(uptr<Node> &root);
    void gen_expr(uptr<Node> &expr);

    void gen_cpd(uptr<Node> &cpd);
    void gen_fdef(uptr<Node> &fdef);
    void gen_fcall(uptr<Node> &fcall);
    void gen_ret(uptr<Node> &ret);
    void gen_val(uptr<Node> &val);
    // repush to top of stack
    void gen_var(uptr<Node> &var);

    void gen_binop(uptr<Node> &op);
    void gen_assign(uptr<Node> &op);

    // push val to stack, track its offset in addr
    void gen_stack_push(const string &val, int &addr);
    // pop stack item into dst
    void gen_stack_pop(const string &dst);

    int addrof(uptr<Node> &node);

private:
    string m_asm;
    int m_rsp=0; // stack ptr

    Scope m_scope;
};
