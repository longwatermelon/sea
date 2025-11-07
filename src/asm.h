#pragma once
#include "node.h"
#include "scope.h"

class Visitor {
public:
    Visitor(Arch arch) : m_arch(arch) {}

    // template <typename NodeT>
    // void visit(NodeT *) {
    //     throw std::logic_error("Visitor::visit missing handler for node type");
    // }

    string gen(Node *root);

    void visit(CpdNode *node);
    void visit(FdefNode *node);
    void visit(FcallNode *node);
    void visit(RetNode *node);
    void visit(ValIntNode *node);
    void visit(ValByteNode *node);
    void visit(BinopNode *node);
    void visit(UnopNode *node);
    void visit(IfNode *node);
    void visit(WhileNode *node);
    void visit(TypevarNode *node);
    void visit(SdefNode *node);
    void visit(BreakNode *node);
    void visit(ContinueNode *node);

    // no-ops
    void visit(VarNode *) {}
    void visit(DtypeNode *) {}

    // delete node's _addr in scope's stack tracking
    void cleanup_dangling(Node *node);
    // adjust m_rsp according to the addresses currently necessary in m_scope
    void tighten_stack();

    void gen_builtin_syscall(FcallNode *fcall);
    void gen_builtin_stalloc(FcallNode *fcall);
    void gen_builtin_sizeof(FcallNode *fcall);
    void gen_builtin_galloc(FcallNode *fcall);

    void gen_assign(BinopNode *op);
    void gen_memb_access(BinopNode *op);
    Addr find_memb_addr(BinopNode *dot);

    void gen_getptr(UnopNode *op);
    void gen_deref(UnopNode *op);

    void gen_global_var(BinopNode *op);

    // push val to stack, track its offset in addr. addr is RBP rel
    Addr gen_stack_push(Addr src, int nbytes);
    // reserve nbytes of space for value, make addr RBP rel
    Addr gen_stack_reserve(int nbytes);
    // mov instruction from src to dst
    // uses x3 if src and dst are both memory refs
    void gen_mov(Addr src, Addr dst, int nbytes);
    // store literal in register (64-bit integer)
    void gen_store_literal(ll val, Addr reg);
    void gen_store_literal(unsigned char val, Addr reg);

    Addr addrof(Node *node);
    DType dtypeof(Node *node);

    Addr regtmp(int n=0) {
        switch (m_arch) {
        // TODO
        case Arch::x86_64: return Addr::reg("%r"+std::to_string(10+n));
        case Arch::ARM64: return Addr::reg("x"+std::to_string(n+9));
        }
    }

    Addr regret() {
        switch (m_arch) {
        case Arch::x86_64: return Addr::reg("%rax");
        case Arch::ARM64: return Addr::reg("x0");
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

    // convert register name to appropriate size for nbytes
    // only handles 1-byte and 8-byte types (by design)
    string reg_for_size(const string& reg, int nbytes) {
        if (nbytes == 8) return reg;  // already 64-bit

        switch (m_arch) {
        case Arch::x86_64: {
            // %rax -> %al, %rbx -> %bl, %r10 -> %r10b, etc.
            if (reg[1] == 'r' && reg.length() > 2 && reg[2] >= 'a' && reg[2] <= 'z') {
                // %rax, %rbx, etc -> %al, %bl, etc
                return "%" + reg.substr(2, 1) + "l";
            } else if (reg[1] == 'r' && reg.length() > 2) {
                // %r10, %r11, etc -> %r10b, %r11b, etc
                return reg + "b";
            }
            return reg;
        }
        case Arch::ARM64: {
            // x0 -> w0, x9 -> w9, etc.
            if (reg.length() > 0 && reg[0] == 'x') {
                return "w" + reg.substr(1);
            }
            return reg;
        }
        }
    }

private:
    void dispatch(Node *node);

    string m_asm, m_asm_data, m_asm_bss;
    // current top of stack, actual stack pointer (capacity)
    int m_tos=0, m_sp=0;

    Scope m_scope;
    vec<SdefNode*> m_sdefs;

    static ll m_galloc_id;

    // loop ids stack for break / continue
    vec<int> m_loop_ids;
    vec<int> m_loop_tos;  // stack depth at start of each loop body

    Arch m_arch;
};
