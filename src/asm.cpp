#include "asm.h"
#include <cassert>

ll Visitor::m_galloc_id = 0;

string Visitor::gen(uptr<Node> &root) {
    m_asm = ".section .text\n";
    m_asm_data = ".section .data\n";
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
                if (expr->def_obj->type == NType::VAR) {
                    Addr addr;
                    gen_stack_reserve(addr);
                    m_scope.create_var(expr->def_obj->var_name, addr, expr->dtype);
                } else if (expr->def_obj->type == NType::BINOP && expr->def_obj->op_type == "=") {
                    Addr addr;
                    gen_stack_reserve(addr);
                    m_scope.create_var(expr->def_obj->op_l->var_name, addr, expr->dtype);
                    gen_expr(expr->def_obj);
                } else {
                    throw std::runtime_error("[Visitor::gen_expr] def_obj wasn't FN or VAR or BINOP assignment");
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
    case NType::STR: gen_str(expr); break;
    }
}

void Visitor::cleanup_dangling(uptr<Node> &node) {
    if (node && node->_addr.type == AType::RBP && node->_addr.exists()) {
        m_scope.del_stkaddr(node->_addr.rbp_addr);
        node->_addr = -1;
    }
}

void Visitor::tighten_stack() {
    int rsp_new = m_scope.top_stkaddr();
    int dif = rsp_new-m_rsp;
    if (dif==0) return;

    m_rsp+=dif;
    m_asm += "\t# tighten_stack\n\taddq $"+std::to_string(dif)+", %rsp\n";
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
    int prev_rsp = m_rsp;
    m_rsp=0;

    // prep params
    int addr=16;
    for (auto &param : fdef->def_obj->fn_args) {
        m_scope.create_var(param->def_obj->var_name, addr, param->dtype);
        // addr+=8;
        addr += dtype_size(param->dtype);
    }

    // fdef
    m_asm += ".global "+fdef->def_obj->fn_name+"\n"+fdef->def_obj->fn_name+":\n";
    m_asm += "\tpush %rbp\n"
             "\tmovq %rsp, %rbp\n\n";

    gen_expr(fdef->def_obj->fn_body);
    // [cleanup] fn body never allocates stack space

    m_asm += "\n\tmovq %rbp, %rsp\n"
             "\tpop %rbp\n"
             "\tret\n\n";

    // restore og scope
    m_rsp = prev_rsp;
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
        gen_stack_mov_raw(addr.repr(), "%rax");

        Addr tmp;
        gen_stack_push("%rax", tmp);
    }

    // call function, store return address on stack
    m_asm += "\tcall "+fcall->fn_name+"\n";

    // [cleanup] args, which are dangling now. do it before pushing fcall result to stack
    // IMPORTANT: none of these ops should touch rax.
    m_scope.del_stkaddr_top_n(sz(fcall->fn_args));
    for (auto &arg : fcall->fn_args) cleanup_dangling(arg);
    tighten_stack();
    // [/cleanup]

    gen_stack_push("%rax", fcall->_addr);
}

void Visitor::gen_builtin_syscall(uptr<Node> &fcall) {
    // push
    vec<string> reg_ord = {"%rax", "%rdi", "%rsi", "%rdx"};
    for (int i=0; i<sz(fcall->fn_args); ++i) {
        gen_expr(fcall->fn_args[i]);
    }

    for (int i=0; i<sz(fcall->fn_args); ++i) {
        Addr addr = addrof(fcall->fn_args[i]);
        gen_stack_mov_raw(addr.repr(), reg_ord[i]);
    }

    // call
    m_asm += "\tsyscall\n";

    // cleanup
    for (auto &x : fcall->fn_args) {
        cleanup_dangling(x);
    }
    tighten_stack();
}

void Visitor::gen_builtin_stalloc(uptr<Node> &fcall) {
    // require 2 argument: a VAL integer (# elements), and a VAR type (element types).
    int cnt = fcall->fn_args[0]->val_int;
    DType type = str2dtype(fcall->fn_args[1]->var_name);
    int bytes = cnt * dtype_size(type);

    // alloc space
    m_asm += "\tsubq $"+std::to_string(bytes)+", %rsp\n";
    m_rsp -= bytes;
    m_scope.claim_stkaddr(m_rsp);

    // return ptr to this space
    gen_stack_mov_raw("%rsp", "%rax");
    gen_stack_push("%rax", fcall->_addr);
}

void Visitor::gen_builtin_sizeof(uptr<Node> &fcall) {
    // require 1 argument: a type.
    // will be parsed as VAR
    DType type = str2dtype(fcall->fn_args[0]->var_name);

    // push ans
    int ans = dtype_size(type);
    gen_stack_push("$"+std::to_string(ans), fcall->_addr);
}

void Visitor::gen_builtin_galloc(uptr<Node> &fcall) {
    // require 2 arguments: VAL int (# elements), VAR (element type).
    int cnt = fcall->fn_args[0]->val_int;
    DType type = str2dtype(fcall->fn_args[1]->var_name);
    int bytes = cnt * dtype_size(type);

    // alloc space
    string label = "_galloc_array_"+std::to_string(m_galloc_id);
    m_galloc_id++;
    m_asm_data += label+": .zero "+std::to_string(bytes)+"\n";

    // return addr
    fcall->_addr = Addr(label);
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    // gen_stack_mov_raw(stkloc(addrof(ret->ret_val)), "%rax");
    gen_stack_mov_raw(addrof(ret->ret_val).repr(), "%rax");
    m_asm += "\tmovq %rbp, %rsp\n"
             "\tpop %rbp\n"
             "\tret\n";
}

void Visitor::gen_val(uptr<Node> &val) {
    switch (val->dtype) {
    case DType::INT: gen_stack_push("$"+std::to_string(val->val_int), val->_addr); break;
    case DType::VOID: throw std::runtime_error("[Visitor::gen_val] unreachable void"); break;
    }
}

void Visitor::gen_binop(uptr<Node> &op) {
    bool math=true;
    string math_expr;
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

    if (math) {
        gen_stack_reserve(op->_addr);
        gen_expr(op->op_l);
        gen_expr(op->op_r);
        gen_stack_mov_raw(addrof(op->op_l).repr(), "%rax");
        gen_stack_mov_raw(addrof(op->op_r).repr(), "%rbx");
        // [cleanup] op_l and op_r are impossible to reference from here on out
        cleanup_dangling(op->op_l);
        cleanup_dangling(op->op_r);
        tighten_stack();
        // [/cleanup]
        m_asm += math_expr;

        string tg = "%rax";
        if (op->op_type == "%") tg = "%rdx";
        gen_stack_mov_raw(tg, op->_addr.repr());
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
        gen_dubref_mov(addrof(op->op_r).repr(), m_scope.find_var(op->op_l->var_name).repr());

        // [cleanup] op_r is useless now that op_l is the handle to op_r's value. op_l is VAR and doesn't need to be cleaned.
        cleanup_dangling(op->op_r);
        tighten_stack();
    } else if (op->op_l->type == NType::UNOP && op->op_l->unop_type == "*") {
        // eval dereferenced object, get loc of it
        gen_expr(op->op_l->unop_obj);
        gen_stack_mov_raw(addrof(op->op_l->unop_obj).repr(), "%rbx");
        gen_stack_mov_raw(addrof(op->op_r).repr(), "%rax");
        gen_stack_mov_raw("%rax", "(%rbx)");

        // [cleanup] TODO
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
        m_asm += "\tleaq "+addrof(op->unop_obj).repr()+", %rax\n";
        // [cleanup]
        cleanup_dangling(op->unop_obj);
        tighten_stack();
        // [/cleanup]
        gen_stack_push("%rax", op->_addr);
    } else if (op->unop_obj->type == NType::UNOP && op->unop_obj->unop_type == "*") {
        // LVALUE DEREF
        gen_expr(op->unop_obj->unop_obj);
        gen_stack_mov_raw(addrof(op->unop_obj->unop_obj).repr(), "%rax");
    }

    gen_stack_push("%rax", op->_addr);
}

void Visitor::gen_deref(uptr<Node> &op) {
    gen_expr(op->unop_obj);
    gen_stack_mov_raw(addrof(op->unop_obj).repr(), "%rax");
    // [cleanup]
    cleanup_dangling(op->unop_obj);
    tighten_stack();
    // [/cleanup]
    gen_stack_push("(%rax)", op->_addr);
}

void Visitor::gen_if(uptr<Node> &node) {
    string else_label = ".L_else_"+std::to_string(node->if_id);
    string end_label = ".L_end_"+std::to_string(node->if_id);

    // conditional
    gen_expr(node->if_cond);
    gen_stack_mov_raw(addrof(node->if_cond).repr(), "%rax");
    // [cleanup] if_cond is dangling now
    cleanup_dangling(node->if_cond);
    tighten_stack();
    // [/cleanup]
    m_asm += "\ttest %rax, %rax\n"
             "\tjz "+else_label+"\n";

    // body
    gen_expr(node->if_body);
    // [cleanup] if_body can technically be non-CPD (`if (x) 5;`) even if it does nothing, cleanup to be safe
    cleanup_dangling(node->if_body);
    tighten_stack();
    // [/cleanup]
    m_asm += "\tjmp "+end_label+"\n";

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
    gen_stack_mov_raw(addrof(node->while_cond).repr(), "%rax");
    // [cleanup] while_cond is dangling now
    cleanup_dangling(node->while_cond);
    tighten_stack();
    // [/cleanup]
    m_asm += "\ttest %rax, %rax\n"
             "\tjz "+end_label+"\n";

    // body
    gen_expr(node->while_body);
    // [cleanup] same reasoning as gen_if
    cleanup_dangling(node->while_body);
    tighten_stack();
    // [/cleanup]
    m_asm += "\tjmp "+start_label+"\n";
    m_asm += end_label+":\n";
}

void Visitor::gen_str(uptr<Node> &node) {
    // TODO TODAY
}

void Visitor::gen_global_var(uptr<Node> &def) {
    string name;
    uptr<Node> *val_node=nullptr;
    if (def->def_obj->type == NType::VAR) {
        name = def->def_obj->var_name;
    } else if (def->def_obj->type == NType::BINOP && def->def_obj->op_type == "=") {
        name = def->def_obj->op_l->var_name;
        val_node = &def->def_obj->op_r;
    } else {
        throw std::runtime_error("[Visitor::gen_global_var] invalid global def");
    }

    // gen val string repr to be assigned
    string val;
    if (val_node) {
        uptr<Node> &node = *val_node;
        // galloc?
        if (node->type == NType::FN) {
            gen_fcall(node);
            // TODO make this less hacky
            val = "_galloc_array_"+std::to_string(m_galloc_id-1);
        } else {
            switch (dtypeof(node)) {
            case DType::INT: val = std::to_string(node->val_int); break;
            case DType::VOID: assert(false); break;
            }
        }
    } else {
        switch (def->dtype) {
        case DType::INT: val = "0"; break;
        case DType::VOID: assert(false); break;
        }
    }

    // gen .data asm
    switch (def->dtype) {
    case DType::INT: m_asm_data += name+": .quad "+val+"\n"; break;
    case DType::VOID: assert(false); break;
    }

    m_scope.create_var(name, Addr(name), def->dtype);
}

void Visitor::gen_stack_push(const string &val, Addr &addr) {
    m_rsp-=8;
    m_scope.claim_stkaddr(m_rsp);
    m_asm += "\tpushq "+val+"\n";
    addr = Addr(m_rsp);
}

void Visitor::gen_stack_reserve(Addr &addr) {
    m_asm += "\tsubq $8, %rsp\n";
    m_rsp-=8;
    m_scope.claim_stkaddr(m_rsp);
    addr = Addr(m_rsp);
}

void Visitor::gen_stack_pop(const string &dst) {
    m_scope.del_stkaddr(m_rsp);
    m_rsp+=8;
    m_asm += "\tpopq "+dst+"\n";
}

void Visitor::gen_dubref_mov(const string &src, const string &dst) {
    gen_stack_mov_raw(src, "%rax");
    gen_stack_mov_raw("%rax", dst);
}

void Visitor::gen_stack_mov_raw(const string &src, const string &dst) {
    m_asm += "\tmovq "+src+", "+dst+"\n";
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
        break;
    }

    return -2;
}

DType Visitor::dtypeof(uptr<Node> &node) {
    switch (node->type) {
    case NType::BINOP: return dtypeof(node->op_l);
    case NType::DEF: return node->dtype;
    case NType::FN: return m_scope.find_fn(node->fn_name).first;
    case NType::UNOP: return dtypeof(node->unop_obj);
    case NType::VAL: return node->dtype;
    case NType::VAR: return m_scope.find_var_dtype(node->var_name);
    case NType::WHILE:
    case NType::STR:
    case NType::RET:
    case NType::IF:
    case NType::CPD:
        break;
    }

    throw std::runtime_error("[Visitor::dtypeof] node doesn't have a dtype, but dtype of node was requested");
}
