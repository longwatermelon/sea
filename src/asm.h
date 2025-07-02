#pragma once
#include "node.h"
#include "scope.h"

class Visitor {
public:
    Visitor()=default;

    string gen(uptr<Node> &root);
    void gen_expr(uptr<Node> &expr);
    // delete node's _addr in scope's stack tracking
    void cleanup_dangling(uptr<Node> &node);
    // adjust m_rsp according to the addresses currently necessary in m_scope
    void tighten_stack();

    void gen_cpd(uptr<Node> &cpd);
    void gen_fdef(uptr<Node> &fdef);
    void gen_fcall(uptr<Node> &fcall);
    void gen_ret(uptr<Node> &ret);
    void gen_val(uptr<Node> &val);
    // repush to top of stack
    void gen_var(uptr<Node> &var);

    void gen_binop(uptr<Node> &op);
    void gen_assign(uptr<Node> &op);

    void gen_unop(uptr<Node> &op);
    void gen_getptr(uptr<Node> &op);
    void gen_deref(uptr<Node> &op);

    void gen_if(uptr<Node> &node);

    // push val to stack, track its offset in addr
    void gen_stack_push(const string &val, int &addr);
    // reserve space for value
    void gen_stack_reserve(int &addr);
    // pop stack item into dst
    void gen_stack_pop(const string &dst);
    // move -src(%rbp) to -dst(%rbp)
    void gen_stack_mov(int src, int dst);
    // move btw/ directly specified locations
    void gen_stack_mov_raw(const string &src, const string &dst);
    // addq on rsp if necessary
    void restore_rsp_scope(int prev_rsp);

    int addrof(uptr<Node> &node);

private:
    string m_asm;
    int m_rsp=0; // stack ptr

    Scope m_scope;
};
