#include "asm.h"
#include <cassert>
#include <functional>

ll Visitor::m_galloc_id = 0;

string Visitor::gen(Node *root) {
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm = ".section .text\n";
        m_asm_data = ".section .data\n.align 8\n";
        m_asm_bss = ".section .bss\n.align 8\n";
    } break;
    case Arch::ARM64: {
        m_asm = ".text\n";
        m_asm_data = ".data\n.align 3\n";
        m_asm_bss = ".bss\n.align 3\n";
    } break;
    }
    dispatch(root);
    return m_asm_data + "\n" + m_asm_bss + "\n" + m_asm;
}

void Visitor::dispatch(Node *expr) {
    if (!expr) return;
    expr->accept(*this);
}

void Visitor::cleanup_dangling(Node *node) {
    if (node && node->_addr.type == AType::RBP && node->_addr.exists()) {
        m_scope.del_stkaddr(node->_addr.rbp_addr);
        node->_addr = Addr::stack(-1);
    }
}

void Visitor::tighten_stack() {
    int tos_new = m_scope.top_stkaddr();
    int dif = tos_new-m_tos;
    if (dif==0) return;

    m_tos+=dif;

    while (m_sp+16 <= m_tos) {
        m_sp += 16;
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\taddq $16, %rsp\n"; break;
        case Arch::ARM64: m_asm += "\tadd sp, sp, #16\n"; break;
        }
    }

    // switch (m_arch) {
    // case Arch::x86_64: m_asm += "\t# tighten_stack\n\taddq $"+std::to_string(dif)+", %rsp\n"; break;
    // case Arch::ARM64: m_asm += "\t// tighten_stack\n\tadd sp, sp, #"+std::to_string(dif)+"\n"; break;
    // }
}

void Visitor::visit(CpdNode *cpd) {
    m_scope.push_layer();
    for (auto &node : cpd->nodes) {
        dispatch(node.get());

        // [cleanup] if node wasn't given a handle here, it won't get one in the next expr
        cleanup_dangling(node.get());
        tighten_stack();
    }
    tighten_stack();
    m_scope.pop_layer();
}

void Visitor::visit(FdefNode *fdef) {
    // add to scope
    vec<DType> scope_args;
    for (uptr<TypevarNode> &param : fdef->params) {
        scope_args.push_back(param->dtype);
    }
    m_scope.create_fn(fdef->name, fdef->ret_dtype, scope_args);

    // declaration?
    if (!fdef->body) {
        return;
    }

    // prep separate scope
    m_scope.push_layer();
    int prev_tos = m_tos, prev_sp = m_sp;
    m_tos=0;
    m_sp=0;

    // prep params
    int addr=16;
    for (uptr<TypevarNode> &param : fdef->params) {
        m_scope.create_var(param->name, Addr::stack(addr), param->dtype);
        addr += dtype_size(param->dtype, m_sdefs);
    }

    // fdef
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += ".global "+fdef->name+"\n"+fdef->name+":\n";
        m_asm += "\tpush %rbp\n"
                 "\tmovq %rsp, %rbp\n\n";
    } break;
    case Arch::ARM64: {
        m_asm += ".global _"+fdef->name+"\n_"+fdef->name+":\n";
        m_asm += "\tstp x29, x30, [sp, #-16]!\n"
                 "\tmov x29, sp\n";
    } break;
    }

    dispatch(fdef->body.get());
    // [cleanup] fn body never allocates stack space

    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\n\tmovq %rbp, %rsp\n"
                 "\tpop %rbp\n"
                 "\tret\n\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\n\tmov sp, x29\n"
                 "\tldp x29, x30, [sp], #16\n"
                 "\tret\n\n";
    } break;
    }

    // restore og scope
    m_tos = prev_tos;
    m_sp = prev_sp;
    m_scope.pop_layer();
}

void Visitor::visit(FcallNode *fcall) {
    if (fcall->name == "syscall") {
        gen_builtin_syscall(fcall);
        return;
    } else if (fcall->name == "stalloc") {
        gen_builtin_stalloc(fcall);
        return;
    } else if (fcall->name == "sizeof") {
        gen_builtin_sizeof(fcall);
        return;
    } else if (fcall->name == "galloc") {
        gen_builtin_galloc(fcall);
        return;
    }

    // TODO type-check against actual args from m_scope
    // eval args, create addresses
    for (uptr<Node> &arg : fcall->args) {
        dispatch(arg.get());
    }

    int s=0;
    for (int i=0; i<sz(fcall->args); ++i) {
        s += dtype_size(dtypeof(fcall->args[i].get()), m_sdefs);
    }

    // ensure m_sp has enough headroom for arguments (move down in 16-byte increments)
    while (m_tos - s < m_sp) {
        m_sp -= 16;
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\tsubq $16, %rsp\n"; break;
        case Arch::ARM64: m_asm += "\tsub sp, sp, #16\n"; break;
        }
    }
    int x = m_tos - m_sp - s;
    // int x = ((-m_tos-s)%16+16)%16;
    Addr pad;
    if (x>0) {
        pad = gen_stack_reserve(x);
    }

    // push args from their cur locations to the front
    for (int i=sz(fcall->args)-1; i>=0; --i) {
        uptr<Node> &arg = fcall->args[i];
        Addr addr = addrof(arg.get());
        gen_mov(addr, regtmp(), dtype_size(dtypeof(arg.get()), m_sdefs));

        Addr tmp = gen_stack_push(regtmp(), dtype_size(dtypeof(arg.get()), m_sdefs));
    }

    // call function, store return address on stack
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tcall "+fcall->name+"\n"; break;
    case Arch::ARM64: m_asm += "\tbl _"+fcall->name+"\n"; break;
    }

    // [cleanup] args, which are dangling now. do it before pushing fcall result to stack
    // IMPORTANT: none of these ops should touch regtmp.
    m_scope.del_stkaddr_top_n(sz(fcall->args));
    for (auto &arg : fcall->args) cleanup_dangling(arg.get());
    if (x>0) {
        m_scope.del_stkaddr(pad.rbp_addr);
    }
    tighten_stack();
    // [/cleanup]

    if (dtypeof(fcall).base != DTypeBase::VOID) {
        fcall->_addr = gen_stack_push(regret(), dtype_size(dtypeof(fcall), m_sdefs));
    }
}

void Visitor::gen_builtin_syscall(FcallNode *fcall) {
    // push
    vec<string> reg_ord;
    switch (m_arch) {
    case Arch::x86_64: reg_ord = {"%rax", "%rdi", "%rsi", "%rdx"}; break;
    case Arch::ARM64: reg_ord = {"x16", "x0", "x1", "x2"}; break;
    }

    for (int i=0; i<sz(fcall->args); ++i) {
        dispatch(fcall->args[i].get());
    }

    for (int i=0; i<sz(fcall->args); ++i) {
        Addr addr = addrof(fcall->args[i].get());
        gen_mov(addr, Addr::reg(reg_ord[i]), dtype_size(dtypeof(fcall->args[i].get()), m_sdefs));
    }

    // call
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tsyscall\n"; break;
    case Arch::ARM64: m_asm += "\tsvc #0\n"; break;
    }

    // cleanup
    for (auto &x : fcall->args) {
        cleanup_dangling(x.get());
    }
    tighten_stack();
}

void Visitor::gen_builtin_stalloc(FcallNode *fcall) {
    // require 2 argument: a VAL integer (# elements), and a DTYPE type (element types).
    ll cnt = dynamic_cast<ValIntNode*>(fcall->args[0].get())->value;
    DType type = dynamic_cast<DtypeNode*>(fcall->args[1].get())->dtype;
    int bytes = (int)(cnt * dtype_size(type, m_sdefs));

    // alloc space
    Addr addr = gen_stack_reserve(bytes);

    // return ptr to this space
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tleaq "+addr.repr(m_arch)+", "+regtmp().repr(m_arch)+"\n"; break;
    case Arch::ARM64: m_asm += "\tadd "+regtmp().repr(m_arch)+", x29, #"+std::to_string(addr.rbp_addr)+"\n"; break;
    }
    // gen_mov(addr, regtmp());
    // push pointer -- size 8.
    fcall->_addr = gen_stack_push(regtmp(), 8);
}

void Visitor::gen_builtin_sizeof(FcallNode *fcall) {
    // require 1 argument: a type.
    DType type = dynamic_cast<DtypeNode*>(fcall->args[0].get())->dtype;

    gen_store_literal((ll)dtype_size(type, m_sdefs), regtmp());
    // 8 bytes because sizeof returns 64-bit int integer
    fcall->_addr = gen_stack_push(regtmp(), 8);
}

void Visitor::gen_builtin_galloc(FcallNode *fcall) {
    // require 2 arguments: VAL int (# elements), DTYPE (element type).
    ll cnt = dynamic_cast<ValIntNode*>(fcall->args[0].get())->value;
    DType type = dynamic_cast<DtypeNode*>(fcall->args[1].get())->dtype;
    int bytes = (int)(cnt * dtype_size(type, m_sdefs));

    // align to 8 bytes
    int aligned_bytes = bytes + ((8 - bytes%8) % 8);

    // alloc space in bss (uninitialized data)
    string label = "_galloc_array_"+std::to_string(m_galloc_id);
    m_galloc_id++;
    m_asm_bss += label+": .zero "+std::to_string(aligned_bytes)+"\n";

    // return addr
    fcall->_addr = Addr::global(label);
}

void Visitor::visit(RetNode *ret) {
    dispatch(ret->expr.get());
    // gen_stack_mov_raw(stkloc(addrof(ret->ret_val)), "%rax");
    gen_mov(addrof(ret->expr.get()), regret(), dtype_size(dtypeof(ret->expr.get()), m_sdefs));
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\n\tmovq %rbp, %rsp\n"
                 "\tpop %rbp\n"
                 "\tret\n\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\n\tmov sp, x29\n"
                 "\tldp x29, x30, [sp], #16\n"
                 "\tret\n\n";
    } break;
    }
}

void Visitor::visit(ValIntNode *val) {
    gen_store_literal(val->value, regtmp());
    // switch (val->val_dtype.base) {
    // case DTypeBase::INT: {
    //     gen_store_literal(val->val_int, regtmp());
    // } break;
    // case DTypeBase::BYTE: {
    //     gen_store_literal(val->val_byte, regtmp());
    // } break;
    // case DTypeBase::STRUCT: {
    //     throw std::runtime_error("[Visitor::gen_val] STRUCT unimplemented for now");
    // } break;
    // case DTypeBase::VOID: throw std::runtime_error("[Visitor::gen_val] unreachable void"); break;
    // }
    val->_addr = gen_stack_push(regtmp(), dtype_size(DType(DTypeBase::INT), m_sdefs));
}

void Visitor::visit(ValByteNode *val) {
    gen_store_literal(val->value, regtmp());
    val->_addr = gen_stack_push(regtmp(), dtype_size(DType(DTypeBase::BYTE), m_sdefs));
}

void Visitor::visit(BinopNode *op) {
    bool math=true;
    string math_expr;

    switch (m_arch) {
    case Arch::x86_64: {
        if (op->type == "+") {
            math_expr = "\taddq %rbx, %rax\n";
        } else if (op->type == "-") {
            math_expr = "\tsubq %rbx, %rax\n";
        } else if (op->type == "*") {
            math_expr = "\timulq %rbx, %rax\n";
        } else if (op->type == "/") {
            math_expr = "\tcqto\n\tidivq %rbx\n";
        } else if (op->type == "%") {
            math_expr = "\tcqto\n\tidivq %rbx\n";
        } else if (op->type == "==") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsete %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->type == "!=") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetne %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->type == "||") {
            math_expr = "\tor %rbx, %rax\n";
        } else if (op->type == "&&") {
            math_expr = "\tand %rbx, %rax\n";
        } else if (op->type == "<") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetl %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->type == ">") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetg %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->type == "<=") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetle %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->type == ">=") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetge %al\n"
                        "\tmovzbl %al, %eax\n";
        } else {
            math=false;
        }
    } break;

    case Arch::ARM64: {
        if (op->type == "+") {
            math_expr = "\tadd x0, x0, x1\n";
        } else if (op->type == "-") {
            math_expr = "\tsub x0, x0, x1\n";
        } else if (op->type == "*") {
            math_expr = "\tmul x0, x0, x1\n";
        } else if (op->type == "/") {
            math_expr = "\tsdiv x0, x0, x1\n";
        } else if (op->type == "%") {
            math_expr = "\tsdiv x2, x0, x1\n\tmsub x0, x2, x1, x0\n";
        } else if (op->type == "==") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, eq\n";
        } else if (op->type == "!=") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, ne\n";
        } else if (op->type == "||") {
            math_expr = "\torr x0, x0, x1\n";
        } else if (op->type == "&&") {
            math_expr = "\tand x0, x0, x1\n";
        } else if (op->type == "<") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, lt\n";
        } else if (op->type == ">") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, gt\n";
        } else if (op->type == "<=") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, le\n";
        } else if (op->type == ">=") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, ge\n";
        } else {
            math=false;
        }
    } break;
    }


    if (math) {
        op->_addr = gen_stack_reserve(dtype_size(dtypeof(op->l.get()), m_sdefs));

        // pointer arithmetic -- special edge case
        if (op->type == "+") {
            DType ldtype = dtypeof(op->l.get());
            if (ldtype.ptrcnt > 0) {
                DType base = ldtype;
                base.ptrcnt--;
                int esize = dtype_size(base, m_sdefs);

                // turn r into a binop *
                auto r = mkuq<BinopNode>();
                r->type = "*";
                r->l = std::move(op->r);

                auto rr = mkuq<ValIntNode>();
                rr->value = esize;
                r->r = std::move(rr);

                op->r = std::move(r);
            }
        }

        dispatch(op->l.get());
        dispatch(op->r.get());
        switch (m_arch) {
        case Arch::x86_64: {
            gen_mov(addrof(op->l.get()), Addr::reg("%rax"), dtype_size(dtypeof(op->l.get()), m_sdefs));
            gen_mov(addrof(op->r.get()), Addr::reg("%rbx"), dtype_size(dtypeof(op->r.get()), m_sdefs));
        } break;
        case Arch::ARM64: {
            gen_mov(addrof(op->l.get()), Addr::reg("x0"), dtype_size(dtypeof(op->l.get()), m_sdefs));
            gen_mov(addrof(op->r.get()), Addr::reg("x1"), dtype_size(dtypeof(op->r.get()), m_sdefs));
        } break;
        }
        // [cleanup] l and r are impossible to reference from here on out
        cleanup_dangling(op->l.get());
        cleanup_dangling(op->r.get());
        tighten_stack();
        // [/cleanup]
        m_asm += math_expr;

        // move to output result of op
        Addr tg;
        switch (m_arch) {
        case Arch::x86_64: {
            tg = Addr::reg("%rax");
            if (op->type == "%") tg = Addr::reg("%rdx");
        } break;
        case Arch::ARM64: {
            tg = Addr::reg("x0");
        } break;
        }
        gen_mov(tg, op->_addr, dtype_size(dtypeof(op), m_sdefs));
    } else {
        if (op->type == "=") {
            gen_assign(op);
        } else if (op->type == ".") {
            gen_memb_access(op);
        }
    }
}

void Visitor::gen_assign(BinopNode *op) {
    // evaluate globals first - we don't want to evaluate op->op_r (in the standard way) if global.
    // gen_global_var has special handling of op_r (like .quad xxx).
    if (dynamic_cast<TypevarNode*>(op->l.get()) && m_scope.layer_count() == 1) {
        gen_global_var(op);
        return;
    }

    // compute op_r if present
    if (op->r) dispatch(op->r.get());

    // stack based stuff
    if (auto *lhs = dynamic_cast<TypevarNode*>(op->l.get())) {
        DType dtype = dtypeof(lhs);
        Addr addr = gen_stack_reserve(dtype_size(dtype, m_sdefs));
        m_scope.create_var(lhs->name, addr, dtype);

        // initializer provided? store into the newly created var
        if (op->r) {
            gen_mov(addrof(op->r.get()), regtmp(), dtype_size(dtypeof(op->r.get()), m_sdefs));
            gen_mov(regtmp(), m_scope.find_var(lhs->name), dtype_size(dtype, m_sdefs));
            cleanup_dangling(op->r.get());
            tighten_stack();
        }
        return;
    } else if (auto *lhs = dynamic_cast<VarNode*>(op->l.get())) {
        // regular var assignment
        assert(m_scope.var_exists(lhs->name));
        gen_mov(addrof(op->r.get()), regtmp(), dtype_size(dtypeof(op->r.get()), m_sdefs));
        gen_mov(regtmp(), m_scope.find_var(lhs->name), dtype_size(dtypeof(lhs), m_sdefs));
        // gen_dubref_mov(addrof(op->op_r).repr(), m_scope.find_var(op->op_l->var_name).repr());

        // [cleanup] op_r is useless now that op_l is the handle to op_r's value. op_l is VAR and doesn't need to be cleaned.
        cleanup_dangling(op->r.get());
        tighten_stack();
    } else if (dynamic_cast<UnopNode*>(op->l.get()) && dynamic_cast<UnopNode*>(op->l.get())->type == "*") {
        auto *lhs = dynamic_cast<UnopNode*>(op->l.get());
        // dereference assign
        dispatch(lhs->obj.get());
        gen_mov(addrof(lhs->obj.get()), regtmp(1), 8);  // pointer is always 8 bytes
        gen_mov(addrof(op->r.get()), regtmp(), dtype_size(dtypeof(op->r.get()), m_sdefs));

        gen_mov(regtmp(), deref_reg(regtmp(1)), dtype_size(dtypeof(lhs), m_sdefs));
        // switch (m_arch) {
        // case Arch::x86_64: gen_mov(regtmp(), deref_reg(regtmp(1))"(%rbx)"); break;
        // case Arch::ARM64: gen_mov("x0", "[x1]"); break;
        // }

        // [cleanup]
        cleanup_dangling(lhs->obj.get());
        tighten_stack();
    } else if (dynamic_cast<BinopNode*>(op->l.get()) && dynamic_cast<BinopNode*>(op->l.get())->type == ".") {
        auto *lhs = dynamic_cast<BinopNode*>(op->l.get());
        // struct member assign
        Addr dst_addr = find_memb_addr(lhs);
        int dst_sz = dtype_size(dtypeof(lhs), m_sdefs);

        gen_mov(addrof(op->r.get()), regtmp(), dtype_size(dtypeof(op->r.get()), m_sdefs));
        gen_mov(regtmp(), dst_addr, dst_sz);

        // [cleanup]
        cleanup_dangling(op->r.get());
        tighten_stack();
    }
}

void Visitor::gen_memb_access(BinopNode *op) {
    Addr addr = find_memb_addr(op);
    DType dtype = dtypeof(op);
    int dtype_sz = dtype_size(dtype, m_sdefs);
    gen_mov(addr, regtmp(), dtype_sz);
    op->_addr = gen_stack_push(regtmp(), dtype_sz);
}

Addr Visitor::find_memb_addr(BinopNode *dot) {
    // accumulate byte offset
    Node *cur = dot;
    int offset = 0;
    while (dynamic_cast<BinopNode*>(cur) && dynamic_cast<BinopNode*>(cur)->type == ".") {
        auto *op = dynamic_cast<BinopNode*>(cur);
        offset += find_member_offset(dtypeof(op->l.get()), dynamic_cast<VarNode*>(op->r.get())->name, m_sdefs);
        cur = op->l.get();
    }
    Node *base = cur;

    auto add_imm = [&](Addr reg, int off) {
        if (off == 0) return;
        switch (m_arch) {
        case Arch::x86_64:
            m_asm += "\taddq $" + std::to_string(off) + ", " + reg.repr(m_arch) + "\n";
            break;
        case Arch::ARM64:
            m_asm += "\tadd " + reg.repr(m_arch) + ", " + reg.repr(m_arch) + ", #" + std::to_string(off) + "\n";
            break;
        }
    };

    // deref? (only case other than var for now)
    if (dynamic_cast<UnopNode*>(base) && dynamic_cast<UnopNode*>(base)->type == "*") {
        auto *unop = dynamic_cast<UnopNode*>(base);
        // base->unop_obj is a pointer
        dispatch(unop->obj.get());
        gen_mov(addrof(unop->obj.get()), regtmp(1), 8);
        add_imm(regtmp(1), offset);

        cleanup_dangling(unop->obj.get());
        tighten_stack();
        return deref_reg(regtmp(1));
    }

    // var
    dispatch(base);
    Addr addr = addrof(base);

    Addr res;
    switch (addr.type) {
    case AType::RBP: {
        addr.rbp_addr += offset;
        res = addr;
    } break;
    case AType::RIP: {
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\tleaq " + addr.repr(m_arch) + ", " + regtmp(1).repr(m_arch) + "\n"; break;
        case Arch::ARM64: {
            m_asm += "\tadrp " + regtmp(1).repr(m_arch) + ", " + addr.rip_addr + "@PAGE\n";
            m_asm += "\tadd " + regtmp(1).repr(m_arch) + ", " + regtmp(1).repr(m_arch) + ", " + addr.rip_addr + "@PAGEOFF\n";
        } break;
        }

        add_imm(regtmp(1), offset);
    } break;
    case AType::REG: {
        // shouldn't happen? no variables should have a home in a register
        throw std::runtime_error("[Visitor::find_memb_addr] base type was REG, doesn't make sense");
    } break;
    }

    cleanup_dangling(base);
    tighten_stack();
    return res;
}

void Visitor::visit(UnopNode *op) {
    if (op->type == "*") {
        gen_deref(op);
    } else if (op->type == "&") {
        gen_getptr(op);
    }
}

void Visitor::gen_getptr(UnopNode *op) {
    if (auto *obj = dynamic_cast<VarNode*>(op->obj.get())) {
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\tleaq "+addrof(obj).repr(m_arch)+", "+regtmp().repr(m_arch)+"\n"; break;
        case Arch::ARM64: {
            Addr objaddr = addrof(obj);
            if (objaddr.type == AType::RBP) {
                m_asm += "\tadd "+regtmp().repr(m_arch)+", x29, #"+std::to_string(objaddr.rbp_addr)+"\n";
            } else {
                m_asm += "\tadrp "+regtmp().repr(m_arch)+", "+objaddr.rip_addr+"@PAGE\n";
                m_asm += "\tadd "+regtmp().repr(m_arch)+", "+regtmp().repr(m_arch)+", "+objaddr.rip_addr+"@PAGEOFF\n";
            }
        } break;
        }
        // [cleanup]
        cleanup_dangling(op->obj.get());
        tighten_stack();
        // [/cleanup]
    } else if (dynamic_cast<UnopNode*>(op->obj.get()) && dynamic_cast<UnopNode*>(op->obj.get())->type == "*") {
        auto *obj = dynamic_cast<UnopNode*>(op->obj.get());
        // LVALUE DEREF
        dispatch(obj->obj.get());
        // 8 bytes: op->obj->obj is a ptr
        gen_mov(addrof(obj->obj.get()), regtmp(), 8);
    }

    // 8 bytes: returning a ptr
    op->_addr = gen_stack_push(regtmp(), 8);
}

void Visitor::gen_deref(UnopNode *op) {
    dispatch(op->obj.get());
    // 8 bytes: store address to be dereferenced
    gen_mov(addrof(op->obj.get()), regtmp(), 8);
    // [cleanup]
    cleanup_dangling(op->obj.get());
    tighten_stack();
    // [/cleanup]
    op->_addr = gen_stack_push(deref_reg(regtmp()), dtype_size(dtypeof(op), m_sdefs));
}

void Visitor::visit(IfNode *node) {
    string else_label = ".L_else_"+std::to_string(node->id);
    string end_label = ".L_end_"+std::to_string(node->id);

    // conditional
    dispatch(node->cond.get());
    gen_mov(addrof(node->cond.get()), regtmp(), dtype_size(dtypeof(node->cond.get()), m_sdefs));
    // [cleanup] if_cond is dangling now
    cleanup_dangling(node->cond.get());
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\ttest "+regtmp().repr(m_arch)+", "+regtmp().repr(m_arch)+"\n"
                 "\tjz "+else_label+"\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\tcbz "+regtmp().repr(m_arch)+", "+else_label+"\n";
    } break;
    }

    // body
    dispatch(node->body.get());
    // [cleanup] if_body can technically be non-CPD (`if (x) 5;`) even if it does nothing, cleanup to be safe
    cleanup_dangling(node->body.get());
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp "+end_label+"\n"; break;
    case Arch::ARM64: m_asm += "\tb "+end_label+"\n"; break;
    }

    // else
    m_asm += else_label+":\n";
    if (node->else_) dispatch(node->else_.get());
    // [cleanup] same reasoning as if_body
    cleanup_dangling(node->else_.get());
    tighten_stack();
    // [/cleanup]
    m_asm += end_label+":\n";
}

void Visitor::visit(WhileNode *node) {
    string start_label = ".L_start_"+std::to_string(node->id);
    string end_label = ".L_end_"+std::to_string(node->id);

    // save stack state for break/continue
    m_loop_ids.push_back(node->id);
    m_loop_tos.push_back(m_tos);

    m_asm += start_label+":\n";

    // cond
    dispatch(node->cond.get());
    gen_mov(addrof(node->cond.get()), regtmp(), dtype_size(dtypeof(node->cond.get()), m_sdefs));
    // [cleanup] cond is dangling now
    cleanup_dangling(node->cond.get());
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\ttest "+regtmp().repr(m_arch)+", "+regtmp().repr(m_arch)+"\n"
                 "\tjz "+end_label+"\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\tcbz "+regtmp().repr(m_arch)+", "+end_label+"\n";
    } break;
    }

    // body
    dispatch(node->body.get());
    m_loop_tos.pop_back();
    m_loop_ids.pop_back();

    // [cleanup] same reasoning as gen_if
    cleanup_dangling(node->body.get());
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp "+start_label+"\n"; break;
    case Arch::ARM64: m_asm += "\tb "+start_label+"\n"; break;
    }
    m_asm += end_label+":\n";
}

void Visitor::visit(ForNode *node) {
    string start_label = ".L_start_" + std::to_string(node->id);
    string end_label = ".L_end_" + std::to_string(node->id);

    // init
    m_scope.push_layer();
    dispatch(node->init.get());

    // save stack state for break/continue
    m_loop_ids.push_back(node->id);
    m_loop_tos.push_back(m_tos);

    m_asm += start_label+":\n";

    // cond
    dispatch(node->cond.get());
    gen_mov(addrof(node->cond.get()), regtmp(), dtype_size(dtypeof(node->cond.get()), m_sdefs));
    // [cleanup] cond is dangling now
    cleanup_dangling(node->cond.get());
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\ttest "+regtmp().repr(m_arch)+", "+regtmp().repr(m_arch)+"\n"
                 "\tjz "+end_label+"\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\tcbz "+regtmp().repr(m_arch)+", "+end_label+"\n";
    } break;
    }

    // body
    dispatch(node->body.get());
    cleanup_dangling(node->body.get());
    tighten_stack();

    // update
    dispatch(node->upd.get());
    cleanup_dangling(node->upd.get());

    m_loop_tos.pop_back();
    m_loop_ids.pop_back();

    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp "+start_label+"\n"; break;
    case Arch::ARM64: m_asm += "\tb "+start_label+"\n"; break;
    }
    m_asm += end_label+":\n";

    m_scope.pop_layer();
    cleanup_dangling(node->init.get());
    tighten_stack();
}

void Visitor::visit(BreakNode *_) {
    if (empty(m_loop_ids)) {
        throw std::runtime_error("break statement outside of loop");
    }

    // restore stack to loop entry state
    int target_tos = m_loop_tos.back();
    int cur_sp = m_sp;
    while (cur_sp + 16 <= target_tos) {
        cur_sp += 16;
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\taddq $16, %rsp\n"; break;
        case Arch::ARM64: m_asm += "\tadd sp, sp, #16\n"; break;
        }
    }

    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp .L_end_" + std::to_string(m_loop_ids.back()) + "\n"; break;
    case Arch::ARM64: m_asm += "\tb .L_end_" + std::to_string(m_loop_ids.back()) + "\n"; break;
    }
}

void Visitor::visit(ContinueNode *_) {
    if (empty(m_loop_ids)) {
        throw std::runtime_error("continue statement outside of loop");
    }

    // restore stack to loop entry state
    int target_tos = m_loop_tos.back();
    int cur_sp = m_sp;
    while (cur_sp + 16 <= target_tos) {
        cur_sp += 16;
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\taddq $16, %rsp\n"; break;
        case Arch::ARM64: m_asm += "\tadd sp, sp, #16\n"; break;
        }
    }

    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp .L_start_" + std::to_string(m_loop_ids.back()) + "\n"; break;
    case Arch::ARM64: m_asm += "\tb .L_start_" + std::to_string(m_loop_ids.back()) + "\n"; break;
    }
}

void Visitor::visit(SdefNode *sdef) {
    m_sdefs.push_back(sdef);
}

void Visitor::visit(TypevarNode *typevar) {
    auto decl = mkuq<BinopNode>();
    decl->type = "=";

    auto lhs = mkuq<TypevarNode>();
    lhs->name = typevar->name;
    lhs->dtype = typevar->dtype;
    decl->l = std::move(lhs);

    gen_assign(decl.get());
}

void Visitor::gen_global_var(BinopNode *op) {
    auto *lhs = dynamic_cast<TypevarNode*>(op->l.get());
    string name = lhs->name;

    // gen val string repr to be assigned
    string val;
    if (op->r) {
        // uptr<Node> &node = op->r;
        // galloc?
        if (auto *r = dynamic_cast<FcallNode*>(op->r.get())) {
            dispatch(r);
            val = "_galloc_array_"+std::to_string(m_galloc_id-1);
        } else {
            switch (dtypeof(op->r.get()).base) {
            case DTypeBase::INT: val = std::to_string(dynamic_cast<ValIntNode*>(op->r.get())->value); break;
            case DTypeBase::BYTE: val = std::to_string(dynamic_cast<ValByteNode*>(op->r.get())->value); break;
            case DTypeBase::STRUCT: assert(false); break; // structs can't be global initialized
            case DTypeBase::VOID: assert(false); break;
            }
        }
    } else {
        switch (dtypeof(op->l.get()).base) {
        case DTypeBase::INT: val = "0"; break;
        case DTypeBase::BYTE: val = "0"; break;
        case DTypeBase::STRUCT: val = ""; break;
        case DTypeBase::VOID: assert(false); break;
        }
    }

    // gen .data asm
    // pointers always use .quad (8 bytes)
    DType dtype = dtypeof(op->l.get());
    if (dtype.ptrcnt > 0) {
        m_asm_data += name+": .quad "+val+"\n";
    } else {
        switch (dtype.base) {
        case DTypeBase::INT: m_asm_data += name+": .quad "+val+"\n"; break;
        case DTypeBase::BYTE: m_asm_data += name+": .byte "+val+"\n"; break;
        // TODO
        case DTypeBase::STRUCT: assert(false); break;
        case DTypeBase::VOID: assert(false); break;
        }
    }

    m_scope.create_var(name, Addr::global(name), dtype);
}

Addr Visitor::gen_stack_push(Addr src, int nbytes) {
    Addr res = gen_stack_reserve(nbytes);
    gen_mov(src, res, nbytes);
    return res;
}

Addr Visitor::gen_stack_reserve(int nbytes) {
    Addr addr;
    switch (m_arch) {
    case Arch::x86_64: {
        m_tos -= nbytes;
        // 16 byte alignment
        while (m_tos < m_sp) {
            m_sp-=16;
            m_asm += "\tsubq $16, %rsp\n";
        }

        m_scope.claim_stkaddr(m_tos);
        addr = Addr::stack(m_tos);
    } break;
    case Arch::ARM64: {
        m_tos -= nbytes;
        // 16 byte alignment (required in arm64)
        while (m_tos < m_sp) {
            m_sp-=16;
            m_asm += "\tsub sp, sp, #16\n";
        }

        m_scope.claim_stkaddr(m_tos);
        addr = Addr::stack(m_tos);
    } break;
    }

    return addr;
}

void Visitor::gen_mov(Addr src, Addr dst, int nbytes) {
    // find free register
    int free_reg=-1;
    for (int i=0; i<=1; ++i) {
        string srcrep = src.is_mem() ? src.repr(m_arch).substr(1,sz(src.repr(m_arch))-2) : src.repr(m_arch);
        string dstrep = dst.is_mem() ? dst.repr(m_arch).substr(1,sz(dst.repr(m_arch))-2) : dst.repr(m_arch);

        bool conflict0 = src.type==AType::REG && srcrep==regtmp(i).repr(m_arch);
        bool conflict1 = dst.type==AType::REG && dstrep==regtmp(i).repr(m_arch);
        if (!conflict0 && !conflict1) {
            free_reg=i;
            break;
        }
    }

    switch (m_arch) {
    case Arch::x86_64: {
        // only byte (1) and int/pointer (8) types
        if (src.is_mem() && dst.is_mem()) {
            gen_mov(src, regtmp(free_reg), nbytes);
            gen_mov(regtmp(free_reg), dst, nbytes);
        } else if (src.is_mem() && !dst.is_mem() && nbytes == 1) {
            // byte load: use movzbq to zero-extend (movb doesn't zero-extend on x86-64)
            m_asm += "\tmovzbq "+src.repr(m_arch)+", "+dst.repr(m_arch)+"\n";
        } else {
            string instr = (nbytes == 1) ? "movb" : "movq";
            string src_repr = src.is_mem() ? src.repr(m_arch) : reg_for_size(src.repr(m_arch), nbytes);
            string dst_repr = dst.is_mem() ? dst.repr(m_arch) : reg_for_size(dst.repr(m_arch), nbytes);
            m_asm += "\t"+instr+" "+src_repr+", "+dst_repr+"\n";
        }
    } break;
    case Arch::ARM64: {
        // only byte (1) and int/pointer (8) types
        string load_instr = (nbytes == 1) ? "ldrb" : "ldr";
        string store_instr = (nbytes == 1) ? "strb" : "str";

        // return true if need immediate outside of [-256,255]
        auto emit_large_offset = [&](int off) {
            if (off < -256 || off > 255) {
                if (off < 0) m_asm += "\tsub x12, x29, #"+std::to_string(abs(off))+"\n";
                else m_asm += "\tadd x12, x29, #"+std::to_string(abs(off))+"\n";
                return true;
            }
            return false;
        };

        // perform mov
        if (src.is_mem() && dst.is_mem()) {
            // MEM -> MEM
            gen_mov(src, regtmp(free_reg), nbytes);
            gen_mov(regtmp(free_reg), dst, nbytes);
        } else if (src.is_mem() && !dst.is_mem()) {
            // MEM -> REG
            if (src.type == AType::RIP) {
                Addr reg = regtmp(free_reg);
                m_asm += "\tadrp "+reg.repr(m_arch)+", "+src.repr(m_arch)+"@PAGE\n"
                         "\t"+load_instr+" "+reg_for_size(dst.repr(m_arch), nbytes)+", ["+reg.repr(m_arch)+", "+src.repr(m_arch)+"@PAGEOFF]\n";
            } else if (src.type == AType::RBP) {
                if (emit_large_offset(src.rbp_addr)) {
                    m_asm += "\t"+load_instr+" "+reg_for_size(dst.repr(m_arch), nbytes)+", [x12]\n";
                } else {
                    m_asm += "\t"+load_instr+" "+reg_for_size(dst.repr(m_arch), nbytes)+", "+src.repr(m_arch)+"\n";
                }
            } else {
                m_asm += "\t"+load_instr+" "+reg_for_size(dst.repr(m_arch), nbytes)+", "+src.repr(m_arch)+"\n";
            }
        } else if (!src.is_mem() && dst.is_mem()) {
            // REG -> MEM
            if (dst.type == AType::RIP) {
                Addr reg = regtmp(free_reg);
                m_asm += "\tadrp "+reg.repr(m_arch)+", "+dst.repr(m_arch)+"@PAGE\n"
                         "\t"+store_instr+" "+reg_for_size(src.repr(m_arch), nbytes)+", ["+reg.repr(m_arch)+", "+dst.repr(m_arch)+"@PAGEOFF]\n";
            } else if (dst.type == AType::RBP) {
                if (emit_large_offset(dst.rbp_addr)) {
                    m_asm += "\t"+store_instr+" "+reg_for_size(src.repr(m_arch), nbytes)+", [x12]\n";
                } else {
                    m_asm += "\t"+store_instr+" "+reg_for_size(src.repr(m_arch), nbytes)+", "+dst.repr(m_arch)+"\n";
                }
            } else {
                m_asm += "\t"+store_instr+" "+reg_for_size(src.repr(m_arch), nbytes)+", "+dst.repr(m_arch)+"\n";
            }
        } else {
            // REG -> REG
            m_asm += "\tmov "+reg_for_size(dst.repr(m_arch), nbytes)+", "+reg_for_size(src.repr(m_arch), nbytes)+"\n";
        }
    } break;
    }
}

void Visitor::gen_store_literal(ll val, Addr reg) {
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tmovq $"+std::to_string(val)+", "+reg.repr(m_arch)+"\n"; break;
    case Arch::ARM64: m_asm += "\tmov "+reg.repr(m_arch)+", #"+std::to_string(val)+"\n"; break;
    }
}

void Visitor::gen_store_literal(unsigned char val, Addr reg) {
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tmovb $"+std::to_string((int)val)+", "+reg_for_size(reg.repr(m_arch), 1)+"\n"; break;
    case Arch::ARM64: m_asm += "\tmov "+reg_for_size(reg.repr(m_arch), 1)+", #"+std::to_string((int)val)+"\n"; break;
    }
}

Addr Visitor::addrof(Node *node) {
    if (dynamic_cast<FcallNode*>(node) ||
        dynamic_cast<ValIntNode*>(node) ||
        dynamic_cast<ValByteNode*>(node) ||
        dynamic_cast<BinopNode*>(node) ||
        dynamic_cast<UnopNode*>(node)) {
        return node->_addr;
    }

    if (auto *var = dynamic_cast<VarNode*>(node)) {
        return m_scope.find_var(var->name);
    }

    assert(false);
}

DType Visitor::dtypeof(Node *node) {
    if (auto *op = dynamic_cast<BinopNode*>(node)) {
        if (op->type == ".") {
            // special struct member access
            DType parent = dtypeof(op->l.get());
            string name = dynamic_cast<VarNode*>(op->r.get())->name;

            for (SdefNode *sdef : m_sdefs) {
                if (sdef->name == parent.struct_name) {
                    for (uptr<TypevarNode> &typevar : sdef->membs) {
                        if (typevar->name == name) {
                            return typevar->dtype;
                        }
                    }

                    throw std::runtime_error("[Visitor::dtypeof] no member '" + name + "' exists in struct '" + parent.struct_name + "'.");
                }
            }
            throw std::runtime_error("[Visitor::dtypeof] no struct '" + parent.struct_name + "' exists.");
        } else {
            // make lhs result type by default
            return dtypeof(op->l.get());
        }
    }

    if (auto *fdef = dynamic_cast<FdefNode*>(node)) {
        return fdef->ret_dtype;
    }

    if (auto *fcall = dynamic_cast<FcallNode*>(node)) {
        // handle builtin functions
        if (fcall->name == "sizeof") {
            return DType(DTypeBase::INT, 0);
        } else if (fcall->name == "syscall") {
            return DType(DTypeBase::INT, 0);
        } else if (fcall->name == "stalloc") {
            return DType(DTypeBase::INT, 1);
        } else if (fcall->name == "galloc") {
            // returns pointer to the element type
            DType elem_type = dtypeof(fcall->args[1].get());
            elem_type.ptrcnt++;
            return elem_type;
        }
        return m_scope.find_fn(fcall->name).first;
    }

    if (auto *unop = dynamic_cast<UnopNode*>(node)) {
        DType dtype = dtypeof(unop->obj.get());
        if (unop->type == "*") dtype.ptrcnt--;
        else if (unop->type == "&") dtype.ptrcnt++;
        return dtype;
    }

    if (dynamic_cast<ValIntNode*>(node)) {
        return DType(DTypeBase::INT);
    }

    if (dynamic_cast<ValByteNode*>(node)) {
        return DType(DTypeBase::BYTE);
    }

    if (auto *var = dynamic_cast<VarNode*>(node)) {
        return m_scope.find_var_dtype(var->name);
    }

    if (auto *dtype = dynamic_cast<DtypeNode*>(node)) {
        return dtype->dtype;
    }

    if (auto *typevar = dynamic_cast<TypevarNode*>(node)) {
        return typevar->dtype;
    }

    throw std::runtime_error("[Visitor::dtypeof] node doesn't have a dtype, but dtype of node was requested");
}
