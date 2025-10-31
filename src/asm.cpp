#include "asm.h"
#include <cassert>

ll Visitor::m_galloc_id = 0;

string Visitor::gen(uptr<Node> &root) {
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
    gen_expr(root);
    return m_asm_data + "\n" + m_asm_bss + "\n" + m_asm;
}

void Visitor::gen_expr(uptr<Node> &expr) {
    switch (expr->type) {
    case NType::CPD: gen_cpd(expr); break;
    case NType::DEF: {
        if (expr->def_obj->type == NType::FN) {
            gen_fdef(expr);
        } else {
            // global or stack based?
            if (m_scope.layer_count()==1) {
                // global
                gen_global_var(expr);
            } else {
                // stack based
                Addr addr = gen_stack_reserve(dtype_size(expr->dtype));
                m_scope.create_var(expr->def_obj->op_l->var_name, addr, expr->dtype);

                // rhs not null? then carry out assign op like normal
                if (expr->def_obj->op_r) {
                    gen_expr(expr->def_obj);
                }
            }
        }
        // [cleanup] FN, VAR, BINOP EQ never allocate stack space
        break;
    }
    case NType::RET: gen_ret(expr); break;
    case NType::VAL: gen_val(expr); break;
    case NType::BINOP: gen_binop(expr); break;
    case NType::UNOP: gen_unop(expr); break;
    case NType::VAR: break; // VAR is just a string handle to m_scope
    case NType::FN: gen_fcall(expr); break;
    case NType::IF: gen_if(expr); break;
    case NType::WHILE: gen_while(expr); break;
    // TODO
    case NType::STR: break;
    case NType::DTYPE: break;
    case NType::BREAK: return gen_break();
    case NType::CONT: return gen_continue();
    }
}

void Visitor::cleanup_dangling(uptr<Node> &node) {
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

void Visitor::gen_cpd(uptr<Node> &cpd) {
    m_scope.push_layer();
    for (auto &node : cpd->cpd_nodes) {
        gen_expr(node);

        // [cleanup] if node wasn't given a handle here, it won't get one in the next expr
        cleanup_dangling(node);
        tighten_stack();
    }
    tighten_stack();
    m_scope.pop_layer();
}

void Visitor::gen_fdef(uptr<Node> &fdef) {
    // add to scope
    vec<DType> scope_args;
    for (auto &arg : fdef->def_obj->fn_args) {
        scope_args.push_back(arg->dtype);
    }
    m_scope.create_fn(fdef->def_obj->fn_name, fdef->dtype, scope_args);

    // declaration?
    if (!fdef->def_obj->fn_body) {
        return;
    }

    // prep separate scope
    m_scope.push_layer();
    int prev_tos = m_tos, prev_sp = m_sp;
    m_tos=0;
    m_sp=0;

    // prep params
    int addr=16;
    for (auto &param : fdef->def_obj->fn_args) {
        m_scope.create_var(param->var_name, Addr::stack(addr), param->dtype);
        addr += dtype_size(param->dtype);
    }

    // fdef
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += ".global "+fdef->def_obj->fn_name+"\n"+fdef->def_obj->fn_name+":\n";
        m_asm += "\tpush %rbp\n"
                 "\tmovq %rsp, %rbp\n\n";
    } break;
    case Arch::ARM64: {
        m_asm += ".global _"+fdef->def_obj->fn_name+"\n_"+fdef->def_obj->fn_name+":\n";
        m_asm += "\tstp x29, x30, [sp, #-16]!\n"
                 "\tmov x29, sp\n";
    } break;
    }

    gen_expr(fdef->def_obj->fn_body);
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

void Visitor::gen_fcall(uptr<Node> &fcall) {
    if (fcall->fn_name == "syscall") {
        gen_builtin_syscall(fcall);
        return;
    } else if (fcall->fn_name == "stalloc") {
        gen_builtin_stalloc(fcall);
        return;
    } else if (fcall->fn_name == "sizeof") {
        gen_builtin_sizeof(fcall);
        return;
    } else if (fcall->fn_name == "galloc") {
        gen_builtin_galloc(fcall);
        return;
    }

    // TODO type-check against actual args from m_scope
    // eval args, create addresses
    for (auto &arg : fcall->fn_args) {
        gen_expr(arg);
    }

    int s=0;
    for (int i=0; i<sz(fcall->fn_args); ++i) {
        s += dtype_size(dtypeof(fcall->fn_args[i]));
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
    for (int i=sz(fcall->fn_args)-1; i>=0; --i) {
        auto &arg = fcall->fn_args[i];
        Addr addr = addrof(arg);
        gen_mov(addr, regtmp(), dtype_size(dtypeof(arg)));

        Addr tmp = gen_stack_push(regtmp(), dtype_size(dtypeof(arg)));
    }

    // call function, store return address on stack
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tcall "+fcall->fn_name+"\n"; break;
    case Arch::ARM64: m_asm += "\tbl _"+fcall->fn_name+"\n"; break;
    }

    // [cleanup] args, which are dangling now. do it before pushing fcall result to stack
    // IMPORTANT: none of these ops should touch regtmp.
    m_scope.del_stkaddr_top_n(sz(fcall->fn_args));
    for (auto &arg : fcall->fn_args) cleanup_dangling(arg);
    if (x>0) {
        m_scope.del_stkaddr(pad.rbp_addr);
    }
    tighten_stack();
    // [/cleanup]

    if (dtypeof(fcall).base != DTypeBase::VOID) {
        fcall->_addr = gen_stack_push(regret(), dtype_size(dtypeof(fcall)));
    }
}

void Visitor::gen_builtin_syscall(uptr<Node> &fcall) {
    // push
    vec<string> reg_ord;
    switch (m_arch) {
    case Arch::x86_64: reg_ord = {"%rax", "%rdi", "%rsi", "%rdx"}; break;
    case Arch::ARM64: reg_ord = {"x16", "x0", "x1", "x2"}; break;
    }

    for (int i=0; i<sz(fcall->fn_args); ++i) {
        gen_expr(fcall->fn_args[i]);
    }

    for (int i=0; i<sz(fcall->fn_args); ++i) {
        Addr addr = addrof(fcall->fn_args[i]);
        gen_mov(addr, Addr::reg(reg_ord[i]), dtype_size(dtypeof(fcall->fn_args[i])));
    }

    // call
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tsyscall\n"; break;
    case Arch::ARM64: m_asm += "\tsvc #0\n"; break;
    }

    // cleanup
    for (auto &x : fcall->fn_args) {
        cleanup_dangling(x);
    }
    tighten_stack();
}

void Visitor::gen_builtin_stalloc(uptr<Node> &fcall) {
    // require 2 argument: a VAL integer (# elements), and a DTYPE type (element types).
    ll cnt = fcall->fn_args[0]->val_int;
    DType type = fcall->fn_args[1]->dtype_type;
    int bytes = (int)(cnt * dtype_size(type));

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

void Visitor::gen_builtin_sizeof(uptr<Node> &fcall) {
    // require 1 argument: a type.
    DType type = fcall->fn_args[0]->dtype_type;

    gen_store_literal((ll)dtype_size(type), regtmp());
    // 8 bytes because sizeof returns 64-bit int integer
    fcall->_addr = gen_stack_push(regtmp(), 8);
}

void Visitor::gen_builtin_galloc(uptr<Node> &fcall) {
    // require 2 arguments: VAL int (# elements), DTYPE (element type).
    ll cnt = fcall->fn_args[0]->val_int;
    DType type = fcall->fn_args[1]->dtype_type;
    int bytes = (int)(cnt * dtype_size(type));

    // align to 8 bytes to ensure proper alignment for subsequent data items
    int aligned_bytes = bytes + ((8 - bytes%8) % 8);

    // alloc space in BSS (uninitialized data)
    string label = "_galloc_array_"+std::to_string(m_galloc_id);
    m_galloc_id++;
    m_asm_bss += label+": .zero "+std::to_string(aligned_bytes)+"\n";

    // return addr
    fcall->_addr = Addr::global(label);
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    // gen_stack_mov_raw(stkloc(addrof(ret->ret_val)), "%rax");
    gen_mov(addrof(ret->ret_val), regret(), dtype_size(dtypeof(ret->ret_val)));
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

void Visitor::gen_val(uptr<Node> &val) {
    switch (val->dtype.base) {
    case DTypeBase::INT: {
        gen_store_literal(val->val_int, regtmp());
    } break;
    case DTypeBase::BYTE: {
        gen_store_literal(val->val_byte, regtmp());
    } break;
    case DTypeBase::VOID: throw std::runtime_error("[Visitor::gen_val] unreachable void"); break;
    }
    val->_addr = gen_stack_push(regtmp(), dtype_size(val->dtype));
}

void Visitor::gen_binop(uptr<Node> &op) {
    bool math=true;
    string math_expr;

    switch (m_arch) {
    case Arch::x86_64: {
        if (op->op_type == "+") {
            math_expr = "\taddq %rbx, %rax\n";
        } else if (op->op_type == "-") {
            math_expr = "\tsubq %rbx, %rax\n";
        } else if (op->op_type == "*") {
            math_expr = "\timulq %rbx, %rax\n";
        } else if (op->op_type == "/") {
            math_expr = "\tcqto\n\tidivq %rbx\n";
        } else if (op->op_type == "%") {
            math_expr = "\tcqto\n\tidivq %rbx\n";
        } else if (op->op_type == "==") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsete %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->op_type == "!=") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetne %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->op_type == "||") {
            math_expr = "\tor %rbx, %rax\n";
        } else if (op->op_type == "&&") {
            math_expr = "\tand %rbx, %rax\n";
        } else if (op->op_type == "<") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetl %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->op_type == ">") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetg %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->op_type == "<=") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetle %al\n"
                        "\tmovzbl %al, %eax\n";
        } else if (op->op_type == ">=") {
            math_expr = "\tcmp %rbx, %rax\n"
                        "\tsetge %al\n"
                        "\tmovzbl %al, %eax\n";
        } else {
            math=false;
        }
    } break;

    case Arch::ARM64: {
        if (op->op_type == "+") {
            math_expr = "\tadd x0, x0, x1\n";
        } else if (op->op_type == "-") {
            math_expr = "\tsub x0, x0, x1\n";
        } else if (op->op_type == "*") {
            math_expr = "\tmul x0, x0, x1\n";
        } else if (op->op_type == "/") {
            math_expr = "\tsdiv x0, x0, x1\n";
        } else if (op->op_type == "%") {
            math_expr = "\tsdiv x2, x0, x1\n\tmsub x0, x2, x1, x0\n";
        } else if (op->op_type == "==") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, eq\n";
        } else if (op->op_type == "!=") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, ne\n";
        } else if (op->op_type == "||") {
            math_expr = "\torr x0, x0, x1\n";
        } else if (op->op_type == "&&") {
            math_expr = "\tand x0, x0, x1\n";
        } else if (op->op_type == "<") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, lt\n";
        } else if (op->op_type == ">") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, gt\n";
        } else if (op->op_type == "<=") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, le\n";
        } else if (op->op_type == ">=") {
            math_expr = "\tcmp x0, x1\n"
                        "\tcset x0, ge\n";
        } else {
            math=false;
        }
    } break;
    }


    if (math) {
        op->_addr = gen_stack_reserve(dtype_size(dtypeof(op->op_l)));

        // pointer arithmetic -- special edge case
        if (op->op_type == "+") {
            DType ldtype = dtypeof(op->op_l);
            if (ldtype.ptrcnt > 0) {
                DType base = ldtype;
                base.ptrcnt--;
                int esize = dtype_size(base);

                // turn op_r into a binop *
                uptr<Node> op_r = mkuq<Node>(NType::BINOP);
                op_r->op_type = "*";
                op_r->op_l = std::move(op->op_r);
                op_r->op_r = mkuq<Node>(NType::VAL, DType(DTypeBase::INT));
                op_r->op_r->val_int = esize;
                op->op_r = std::move(op_r);
            }
        }

        gen_expr(op->op_l);
        gen_expr(op->op_r);
        switch (m_arch) {
        case Arch::x86_64: {
            gen_mov(addrof(op->op_l), Addr::reg("%rax"), dtype_size(dtypeof(op->op_l)));
            gen_mov(addrof(op->op_r), Addr::reg("%rbx"), dtype_size(dtypeof(op->op_r)));
        } break;
        case Arch::ARM64: {
            gen_mov(addrof(op->op_l), Addr::reg("x0"), dtype_size(dtypeof(op->op_l)));
            gen_mov(addrof(op->op_r), Addr::reg("x1"), dtype_size(dtypeof(op->op_r)));
        } break;
        }
        // [cleanup] op_l and op_r are impossible to reference from here on out
        cleanup_dangling(op->op_l);
        cleanup_dangling(op->op_r);
        tighten_stack();
        // [/cleanup]
        m_asm += math_expr;

        // move to output result of op
        Addr tg;
        switch (m_arch) {
        case Arch::x86_64: {
            tg = Addr::reg("%rax");
            if (op->op_type == "%") tg = Addr::reg("%rdx");
        } break;
        case Arch::ARM64: {
            tg = Addr::reg("x0");
        } break;
        }
        gen_mov(tg, op->_addr, dtype_size(dtypeof(op)));
    } else {
        if (op->op_type == "=") {
            gen_assign(op);
        }
    }
}

void Visitor::gen_assign(uptr<Node> &op) {
    // compute op_r
    gen_expr(op->op_r);

    if (op->op_l->type == NType::VAR) {
        // move result to var in op_l
        assert(m_scope.var_exists(op->op_l->var_name));
        // load with source size, store with dest size for automatic widening/narrowing
        gen_mov(addrof(op->op_r), regtmp(), dtype_size(dtypeof(op->op_r)));
        gen_mov(regtmp(), m_scope.find_var(op->op_l->var_name), dtype_size(dtypeof(op->op_l)));
        // gen_dubref_mov(addrof(op->op_r).repr(), m_scope.find_var(op->op_l->var_name).repr());

        // [cleanup] op_r is useless now that op_l is the handle to op_r's value. op_l is VAR and doesn't need to be cleaned.
        cleanup_dangling(op->op_r);
        tighten_stack();
    } else if (op->op_l->type == NType::UNOP && op->op_l->unop_type == "*") {
        // eval dereferenced object, get loc of it
        gen_expr(op->op_l->unop_obj);
        gen_mov(addrof(op->op_l->unop_obj), regtmp(1), 8);  // pointer is always 8 bytes
        // load with source size, store with dest size for automatic widening/narrowing
        gen_mov(addrof(op->op_r), regtmp(), dtype_size(dtypeof(op->op_r)));

        gen_mov(regtmp(), deref_reg(regtmp(1)), dtype_size(dtypeof(op->op_l)));
        // switch (m_arch) {
        // case Arch::x86_64: gen_mov(regtmp(), deref_reg(regtmp(1))"(%rbx)"); break;
        // case Arch::ARM64: gen_mov("x0", "[x1]"); break;
        // }

        // [cleanup]
        cleanup_dangling(op->op_l->unop_obj);
        tighten_stack();
    }
}

void Visitor::gen_unop(uptr<Node> &op) {
    if (op->unop_type == "*") {
        gen_deref(op);
    } else if (op->unop_type == "&") {
        gen_getptr(op);
    }
}

void Visitor::gen_getptr(uptr<Node> &op) {
    if (op->unop_obj->type == NType::VAR) {
        switch (m_arch) {
        case Arch::x86_64: m_asm += "\tleaq "+addrof(op->unop_obj).repr(m_arch)+", "+regtmp().repr(m_arch)+"\n"; break;
        case Arch::ARM64: {
            Addr objaddr = addrof(op->unop_obj);
            if (objaddr.type == AType::RBP) {
                m_asm += "\tadd "+regtmp().repr(m_arch)+", x29, #"+std::to_string(objaddr.rbp_addr)+"\n";
            } else {
                m_asm += "\tadrp "+regtmp().repr(m_arch)+", "+objaddr.rip_addr+"@PAGE\n";
                m_asm += "\tadd "+regtmp().repr(m_arch)+", "+regtmp().repr(m_arch)+", "+objaddr.rip_addr+"@PAGEOFF\n";
            }
        } break;
        }
        // [cleanup]
        cleanup_dangling(op->unop_obj);
        tighten_stack();
        // [/cleanup]
    } else if (op->unop_obj->type == NType::UNOP && op->unop_obj->unop_type == "*") {
        // LVALUE DEREF
        gen_expr(op->unop_obj->unop_obj);
        gen_mov(addrof(op->unop_obj->unop_obj), regtmp(), 8);  // pointer is always 8 bytes
    }

    // pointers are always 8 bytes
    op->_addr = gen_stack_push(regtmp(), 8);
}

void Visitor::gen_deref(uptr<Node> &op) {
    gen_expr(op->unop_obj);
    gen_mov(addrof(op->unop_obj), regtmp(), 8);  // pointer is always 8 bytes
    // [cleanup]
    cleanup_dangling(op->unop_obj);
    tighten_stack();
    // [/cleanup]
    op->_addr = gen_stack_push(deref_reg(regtmp()), dtype_size(dtypeof(op)));
}

void Visitor::gen_if(uptr<Node> &node) {
    string else_label = ".L_else_"+std::to_string(node->if_id);
    string end_label = ".L_end_"+std::to_string(node->if_id);

    // conditional
    gen_expr(node->if_cond);
    gen_mov(addrof(node->if_cond), regtmp(), dtype_size(dtypeof(node->if_cond)));
    // [cleanup] if_cond is dangling now
    cleanup_dangling(node->if_cond);
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
    gen_expr(node->if_body);
    // [cleanup] if_body can technically be non-CPD (`if (x) 5;`) even if it does nothing, cleanup to be safe
    cleanup_dangling(node->if_body);
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp "+end_label+"\n"; break;
    case Arch::ARM64: m_asm += "\tb "+end_label+"\n"; break;
    }

    // else
    m_asm += else_label+":\n";
    if (node->if_else) gen_expr(node->if_else);
    // [cleanup] same reasoning as if_body
    cleanup_dangling(node->if_else);
    tighten_stack();
    // [/cleanup]
    m_asm += end_label+":\n";
}

void Visitor::gen_while(uptr<Node> &node) {
    string start_label = ".L_start_"+std::to_string(node->while_id);
    string end_label = ".L_end_"+std::to_string(node->while_id);

    // save stack state for break/continue
    m_loop_ids.push_back(node->while_id);
    m_loop_tos.push_back(m_tos);

    m_asm += start_label+":\n";

    // cond
    gen_expr(node->while_cond);
    gen_mov(addrof(node->while_cond), regtmp(), dtype_size(dtypeof(node->while_cond)));
    // [cleanup] while_cond is dangling now
    cleanup_dangling(node->while_cond);
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
    gen_expr(node->while_body);
    m_loop_tos.pop_back();
    m_loop_ids.pop_back();

    // [cleanup] same reasoning as gen_if
    cleanup_dangling(node->while_body);
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tjmp "+start_label+"\n"; break;
    case Arch::ARM64: m_asm += "\tb "+start_label+"\n"; break;
    }
    m_asm += end_label+":\n";
}

void Visitor::gen_break() {
    if (empty(m_loop_ids)) {
        throw std::runtime_error("break statement outside of loop");
    }

    // restore stack to loop entry state before jumping
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

void Visitor::gen_continue() {
    if (empty(m_loop_ids)) {
        throw std::runtime_error("continue statement outside of loop");
    }

    // restore stack to loop entry state before jumping
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

void Visitor::gen_global_var(uptr<Node> &def) {
    string name = def->def_obj->op_l->var_name;;

    // gen val string repr to be assigned
    string val;
    if (def->def_obj->op_r) {
        uptr<Node> &node = def->def_obj->op_r;
        // galloc?
        if (node->type == NType::FN) {
            gen_fcall(node);
            // TODO make this less hacky
            val = "_galloc_array_"+std::to_string(m_galloc_id-1);
        } else {
            switch (dtypeof(node).base) {
            case DTypeBase::INT: val = std::to_string(node->val_int); break;
            case DTypeBase::BYTE: val = std::to_string((int)node->val_byte); break;
            case DTypeBase::VOID: assert(false); break;
            }
        }
    } else {
        switch (def->dtype.base) {
        case DTypeBase::INT: val = "0"; break;
        case DTypeBase::BYTE: val = "0"; break;
        case DTypeBase::VOID: assert(false); break;
        }
    }

    // gen .data asm
    // pointers always use .quad (8 bytes)
    if (def->dtype.ptrcnt > 0) {
        m_asm_data += name+": .quad "+val+"\n";
    } else {
        switch (def->dtype.base) {
        case DTypeBase::INT: m_asm_data += name+": .quad "+val+"\n"; break;
        case DTypeBase::BYTE: m_asm_data += name+": .byte "+val+"\n"; break;
        case DTypeBase::VOID: assert(false); break;
        }
    }

    m_scope.create_var(name, Addr::global(name), def->dtype);
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
            } else {
                m_asm += "\t"+load_instr+" "+reg_for_size(dst.repr(m_arch), nbytes)+", "+src.repr(m_arch)+"\n";
            }
        } else if (!src.is_mem() && dst.is_mem()) {
            // REG -> MEM
            if (dst.type == AType::RIP) {
                Addr reg = regtmp(free_reg);
                m_asm += "\tadrp "+reg.repr(m_arch)+", "+dst.repr(m_arch)+"@PAGE\n"
                         "\t"+store_instr+" "+reg_for_size(src.repr(m_arch), nbytes)+", ["+reg.repr(m_arch)+", "+dst.repr(m_arch)+"@PAGEOFF]\n";
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

Addr Visitor::addrof(uptr<Node> &node) {
    switch (node->type) {
    case NType::FN: return node->_addr;
    case NType::VAL: return node->_addr;
    case NType::VAR: return m_scope.find_var(node->var_name);
    case NType::BINOP: return node->_addr;
    case NType::UNOP: return node->_addr;
    case NType::STR: return node->_addr;
    case NType::CPD:
    case NType::DEF:
    case NType::RET:
    case NType::IF:
    case NType::WHILE:
    case NType::DTYPE:
    case NType::BREAK:
    case NType::CONT:
        break;
    }

    assert(false);
}

DType Visitor::dtypeof(uptr<Node> &node) {
    switch (node->type) {
    case NType::BINOP: return dtypeof(node->op_l);
    case NType::DEF: return node->dtype;
    case NType::FN: {
        // handle builtin functions
        if (node->fn_name == "sizeof") {
            return DType(DTypeBase::INT, 0);
        } else if (node->fn_name == "syscall") {
            return DType(DTypeBase::INT, 0);
        } else if (node->fn_name == "stalloc") {
            return DType(DTypeBase::INT, 1);  // pointer
        } else if (node->fn_name == "galloc") {
            // returns pointer to the element type
            DType elem_type = node->fn_args[1]->dtype_type;
            elem_type.ptrcnt++;
            return elem_type;
        }
        return m_scope.find_fn(node->fn_name).first;
    }
    case NType::UNOP: {
        DType dtype = dtypeof(node->unop_obj);
        if (node->unop_type == "*") dtype.ptrcnt--;
        else if (node->unop_type == "&") dtype.ptrcnt++;
        return dtype;
    } break;
    case NType::VAL: return node->dtype;
    case NType::VAR: return m_scope.find_var_dtype(node->var_name);
    case NType::DTYPE: return node->dtype_type;
    case NType::WHILE:
    case NType::STR:
    case NType::RET:
    case NType::IF:
    case NType::CPD:
    case NType::BREAK:
    case NType::CONT:
        break;
    }

    throw std::runtime_error("[Visitor::dtypeof] node doesn't have a dtype, but dtype of node was requested");
}
