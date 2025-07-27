#include "asm.h"
#include <cassert>

ll Visitor::m_galloc_id = 0;

string Visitor::gen(uptr<Node> &root) {
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm = ".section .text\n";
        m_asm_data = ".section .data\n";
    } break;
    case Arch::ARM64: {
        m_asm = ".text\n";
        m_asm_data = ".data\n";
    } break;
    }
    gen_expr(root);
    return m_asm_data + "\n" + m_asm;
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
    int prev_tos = m_tos;
    m_tos=0;

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
        m_asm += ".global "+fdef->def_obj->fn_name+"\n"+fdef->def_obj->fn_name+":\n";
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
    // push args from their cur locations to the front
    for (int i=sz(fcall->fn_args)-1; i>=0; --i) {
        auto &arg = fcall->fn_args[i];
        Addr addr = addrof(arg);
        gen_mov(addr, regtmp());

        Addr tmp = gen_stack_push(regtmp(), dtype_size(dtypeof(arg)));
    }

    // call function, store return address on stack
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tcall "+fcall->fn_name+"\n"; break;
    case Arch::ARM64: m_asm += "\tbl "+fcall->fn_name+"\n"; break;
    }

    // [cleanup] args, which are dangling now. do it before pushing fcall result to stack
    // IMPORTANT: none of these ops should touch regtmp.
    m_scope.del_stkaddr_top_n(sz(fcall->fn_args));
    for (auto &arg : fcall->fn_args) cleanup_dangling(arg);
    tighten_stack();
    // [/cleanup]

    fcall->_addr = gen_stack_push(regtmp(), dtype_size(dtypeof(fcall)));
}

void Visitor::gen_builtin_syscall(uptr<Node> &fcall) {
    // push
    vec<string> reg_ord;
    switch (m_arch) {
    case Arch::x86_64: reg_ord = {"%rax", "%rdi", "%rsi", "%rdx"}; break;
    case Arch::ARM64: reg_ord = {"x8", "x0", "x1", "x2"}; break;
    }

    for (int i=0; i<sz(fcall->fn_args); ++i) {
        gen_expr(fcall->fn_args[i]);
    }

    for (int i=0; i<sz(fcall->fn_args); ++i) {
        Addr addr = addrof(fcall->fn_args[i]);
        gen_mov(addr, Addr::reg(reg_ord[i]));
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
    int cnt = fcall->fn_args[0]->val_int;
    DType type = fcall->fn_args[1]->dtype_type;
    int bytes = cnt * dtype_size(type);

    // alloc space
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tsubq $"+std::to_string(bytes)+", %rsp\n"; break;
    case Arch::ARM64: m_asm += "\tsub sp, sp, #"+std::to_string(bytes)+"\n"; break;
    }
    m_tos -= bytes;
    m_scope.claim_stkaddr(m_tos);

    // return ptr to this space
    gen_mov(Addr::stack(m_tos), regtmp());
    fcall->_addr = gen_stack_push(regtmp(), dtype_size(dtypeof(fcall)));
}

void Visitor::gen_builtin_sizeof(uptr<Node> &fcall) {
    // require 1 argument: a type.
    DType type = fcall->fn_args[0]->dtype_type;

    gen_store_literal(dtype_size(type), regtmp());
    // 8 bytes because sizeof returns 64-bit int integer
    gen_stack_push(regtmp(), 8);
}

void Visitor::gen_builtin_galloc(uptr<Node> &fcall) {
    // require 2 arguments: VAL int (# elements), DTYPE (element type).
    int cnt = fcall->fn_args[0]->val_int;
    DType type = fcall->fn_args[1]->dtype_type;
    int bytes = cnt * dtype_size(type);

    // alloc space
    string label = "_galloc_array_"+std::to_string(m_galloc_id);
    m_galloc_id++;
    m_asm_data += label+": .zero "+std::to_string(bytes)+"\n";

    // return addr
    fcall->_addr = Addr::global(label);
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    // gen_stack_mov_raw(stkloc(addrof(ret->ret_val)), "%rax");
    gen_mov(addrof(ret->ret_val), regtmp());
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
        val->_addr = gen_stack_push(regtmp(), dtype_size(DType(DTypeBase::INT)));
    } break;
    case DTypeBase::VOID: throw std::runtime_error("[Visitor::gen_val] unreachable void"); break;
    }
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
            math_expr = "\tsdiv x2, x0, x1\nmsub x0, x2, x1, x0\n";
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
        gen_mov(addrof(op->op_l), regtmp());
        gen_mov(addrof(op->op_r), regtmp(1));
        // [cleanup] op_l and op_r are impossible to reference from here on out
        cleanup_dangling(op->op_l);
        cleanup_dangling(op->op_r);
        tighten_stack();
        // [/cleanup]
        m_asm += math_expr;

        Addr tg = regtmp();
        if (m_arch == Arch::x86_64 && op->op_type == "%") tg = Addr::reg("%rdx");
        gen_mov(tg, op->_addr);
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
        gen_mov(addrof(op->op_r), regtmp());
        gen_mov(regtmp(), m_scope.find_var(op->op_l->var_name));
        // gen_dubref_mov(addrof(op->op_r).repr(), m_scope.find_var(op->op_l->var_name).repr());

        // [cleanup] op_r is useless now that op_l is the handle to op_r's value. op_l is VAR and doesn't need to be cleaned.
        cleanup_dangling(op->op_r);
        tighten_stack();
    } else if (op->op_l->type == NType::UNOP && op->op_l->unop_type == "*") {
        // eval dereferenced object, get loc of it
        gen_expr(op->op_l->unop_obj);
        gen_mov(addrof(op->op_l->unop_obj), regtmp(1));
        gen_mov(addrof(op->op_r), regtmp());

        gen_mov(regtmp(), deref_reg(regtmp(1)));
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
        m_asm += "\tleaq "+addrof(op->unop_obj).repr(m_arch)+", %rax\n";
        // [cleanup]
        cleanup_dangling(op->unop_obj);
        tighten_stack();
        // [/cleanup]
    } else if (op->unop_obj->type == NType::UNOP && op->unop_obj->unop_type == "*") {
        // LVALUE DEREF
        gen_expr(op->unop_obj->unop_obj);
        gen_mov(addrof(op->unop_obj->unop_obj), regtmp());
    }

    // TODO un-hardcode ptr size of 8
    op->_addr = gen_stack_push(regtmp(), 8);
}

void Visitor::gen_deref(uptr<Node> &op) {
    gen_expr(op->unop_obj);
    gen_mov(addrof(op->unop_obj), regtmp());
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
    gen_mov(addrof(node->if_cond), regtmp());
    // [cleanup] if_cond is dangling now
    cleanup_dangling(node->if_cond);
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\ttest %rax, %rax\n"
                 "\tjz "+else_label+"\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\tcbz x0, "+else_label+"\n";
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
    m_asm += start_label+":\n";

    // cond
    gen_expr(node->while_cond);
    gen_mov(addrof(node->while_cond), regtmp());
    // [cleanup] while_cond is dangling now
    cleanup_dangling(node->while_cond);
    tighten_stack();
    // [/cleanup]
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\ttest %rax, %rax\n"
                 "\tjz "+end_label+"\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\tcbz x0, "+end_label+"\n";
    } break;
    }

    // body
    gen_expr(node->while_body);
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
            case DTypeBase::VOID: assert(false); break;
            }
        }
    } else {
        switch (def->dtype.base) {
        case DTypeBase::INT: val = "0"; break;
        case DTypeBase::VOID: assert(false); break;
        }
    }

    // gen .data asm
    switch (def->dtype.base) {
    case DTypeBase::INT: m_asm_data += name+": .quad "+val+"\n"; break;
    case DTypeBase::VOID: assert(false); break;
    }

    m_scope.create_var(name, Addr::global(name), def->dtype);
}

Addr Visitor::gen_stack_push(Addr src, int nbytes) {
    Addr res = gen_stack_reserve(nbytes);
    gen_mov(src, res);
    return res;
}

Addr Visitor::gen_stack_reserve(int nbytes) {
    Addr addr;
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\tsubq $"+std::to_string(nbytes)+", %rsp\n";
        m_tos-=nbytes;
        m_sp-=nbytes;
        m_scope.claim_stkaddr(m_tos);
        addr = Addr::stack(m_tos);
    } break;
    case Arch::ARM64: {
        m_tos -= nbytes;
        // sp must be 16 byte aligned in arm64
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

void Visitor::gen_mov(Addr src, Addr dst) {
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\tmovq "+src.repr(m_arch)+", "+dst.repr(m_arch)+"\n";
    } break;
    case Arch::ARM64: {
        if (src.type == AType::RBP) {
            m_asm += "\tldr "+dst.repr(m_arch)+", "+src.repr(m_arch)+"\n";
        } else if (dst.type == AType::RBP) {
            m_asm += "\tstr "+src.repr(m_arch)+", "+dst.repr(m_arch)+"\n";
        } else if (src.type == AType::RIP) {
            string reg = dst.repr(m_arch)=="x0"?"x1":"x0";
            m_asm += "\tadrp "+reg+", "+src.repr(m_arch)+"\n"
                     "\tldr "+dst.repr(m_arch)+", ["+reg+", :lo12:"+src.repr(m_arch)+"]\n";
        } else if (dst.type == AType::RIP) {
            string reg = src.repr(m_arch)=="x0"?"x1":"x0";
            m_asm += "\tadrp "+reg+", "+dst.repr(m_arch)+"\n"
                     "\tstr "+src.repr(m_arch)+", ["+reg+", :lo12:"+dst.repr(m_arch)+"]\n";
        } else {
            m_asm += "\tmov "+dst.repr(m_arch)+", "+src.repr(m_arch)+"\n";
        }
    } break;
    }
}

Addr Visitor::gen_load_global_addr(Addr addr, int reg_num) {
    Addr reg = regtmp(reg_num);
    switch (m_arch) {
    case Arch::x86_64: {
        m_asm += "\tleaq "+addr.repr(m_arch)+", "+reg.repr(m_arch)+"\n";
    } break;
    case Arch::ARM64: {
        m_asm += "\tadrp "+reg.repr(m_arch)+", "+addr.repr(m_arch)+"\n"
                 "\tadd "+reg.repr(m_arch)+", "+reg.repr(m_arch)+", :lo12:"+addr.repr(m_arch)+"\n";
    } break;
    }
    return deref_reg(reg);
}

void Visitor::gen_store_literal(int val, Addr reg) {
    switch (m_arch) {
    case Arch::x86_64: m_asm += "\tmovq $"+std::to_string(val)+", "+reg.repr(m_arch)+"\n"; break;
    case Arch::ARM64: m_asm += "\tmov "+reg.repr(m_arch)+", #"+std::to_string(val)+"\n"; break;
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
        break;
    }

    assert(false);
}

DType Visitor::dtypeof(uptr<Node> &node) {
    switch (node->type) {
    case NType::BINOP: return dtypeof(node->op_l);
    case NType::DEF: return node->dtype;
    case NType::FN: return m_scope.find_fn(node->fn_name).first;
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
        break;
    }

    throw std::runtime_error("[Visitor::dtypeof] node doesn't have a dtype, but dtype of node was requested");
}
