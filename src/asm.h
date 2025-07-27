#pragma once
#include "node.h"
#include "scope.h"

class Visitor {
public:
    Visitor(Arch arch) : m_arch(arch) {}

    string gen(uptr<Node> &root);
    void gen_expr(uptr<Node> &expr);
    // delete node's _addr in scope's stack tracking
    void cleanup_dangling(uptr<Node> &node);
    // adjust m_rsp according to the addresses currently necessary in m_scope
    void tighten_stack();

    void gen_cpd(uptr<Node> &cpd);
    void gen_fdef(uptr<Node> &fdef);
    void gen_fcall(uptr<Node> &fcall);
    void gen_builtin_syscall(uptr<Node> &fcall);
    void gen_builtin_stalloc(uptr<Node> &fcall);
    void gen_builtin_sizeof(uptr<Node> &fcall);
    void gen_builtin_galloc(uptr<Node> &fcall);
    void gen_ret(uptr<Node> &ret);
    void gen_val(uptr<Node> &val);

    void gen_binop(uptr<Node> &op);
    void gen_assign(uptr<Node> &op);

    void gen_unop(uptr<Node> &op);
    void gen_getptr(uptr<Node> &op);
    void gen_deref(uptr<Node> &op);

    void gen_if(uptr<Node> &node);
    void gen_while(uptr<Node> &node);

    void gen_global_var(uptr<Node> &def);

    // push val to stack, track its offset in addr. addr is RBP rel
    Addr gen_stack_push(Addr src, int nbytes);
    // reserve nbytes of space for value, make addr RBP rel
    Addr gen_stack_reserve(int nbytes);
    // mov instruction from src to dst
    void gen_mov(Addr src, Addr dst);
    // load global from addr into register
    Addr gen_load_global_addr(Addr addr, int reg_num);
    // store literal in register
    void gen_store_literal(int val, Addr reg);

    Addr addrof(uptr<Node> &node);
    DType dtypeof(uptr<Node> &node);

    Addr regtmp(int n=0) {
        switch (m_arch) {
        case Arch::x86_64: return Addr::reg("%r"+string(1,'a'+n)+"x");
        case Arch::ARM64: return Addr::reg("x"+std::to_string(n));
        }
    }

    Addr deref_reg(Addr addr) {
        string name = addr.repr(m_arch);
        switch (m_arch) {
        case Arch::x86_64: name = "("+name+")"; break;
        case Arch::ARM64: name = "["+name+"]"; break;
        }

        Addr res = addr;
        res.reg_name = name;
        return res;
    }

private:
    string m_asm, m_asm_data;
    // current top of stack, actual stack pointer (capacity)
    int m_tos=0, m_sp=0;

    Scope m_scope;

    static ll m_galloc_id;

    Arch m_arch;
};
