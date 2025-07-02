#include "asm.h"
#include <cassert>

string Visitor::gen(uptr<Node> &root) {
    m_asm = ".section .text\n"
            "\t.global _start\n\n"
            "_start:\n"
            "\tcall main\n"
            "\tmovq %rax, %rdi\n"
            "\tmovq $60, %rax\n"
            "\tsyscall\n\n";

    gen_expr(root);
    return m_asm;
}

void Visitor::gen_expr(uptr<Node> &expr) {
    switch (expr->type) {
    case NType::CPD: gen_cpd(expr); break;
    case NType::DEF: {
        if (expr->def_obj->type == NType::FN) {
            gen_fdef(expr);
        } else if (expr->def_obj->type == NType::VAR) {
            int addr;
            gen_stack_reserve(addr);
            m_scope.create_var(expr->def_obj->var_name, addr, expr->dtype);
        } else if (expr->def_obj->type == NType::BINOP && expr->def_obj->op_type == "=") {
            int addr;
            gen_stack_reserve(addr);
            m_scope.create_var(expr->def_obj->op_l->var_name, addr, expr->dtype);
            gen_expr(expr->def_obj);
        } else {
            throw std::runtime_error("[Visitor::gen_expr] def_obj wasn't FN or VAR or BINOP assignment");
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
    }
}

void Visitor::cleanup_dangling(uptr<Node> &node) {
    if (node && node->_addr != -1) {
        m_scope.del_addr(node->_addr);
        node->_addr = -1;
    }
}

void Visitor::tighten_stack() {
    int dif=0;
    while (m_rsp+dif<0 && !m_scope.check_addr(m_rsp+dif)) {
        dif+=8;
    }
    if (dif==0) return;

    m_rsp+=dif;
    m_asm += "\t# tighten_stack\n\taddq $"+std::to_string(dif)+", %rsp\n";
}

void Visitor::gen_cpd(uptr<Node> &cpd) {
    m_scope.push_layer();
    int rsp = m_rsp;
    for (auto &node : cpd->cpd_nodes) {
        gen_expr(node);

        // [cleanup] if node wasn't given a handle here, it won't get one in the next expr
        cleanup_dangling(node);
        tighten_stack();
    }
    restore_rsp_scope(rsp);
    m_scope.pop_layer();
}

void Visitor::gen_fdef(uptr<Node> &fdef) {
    // add to scope
    vec<DType> scope_args;
    for (auto &arg : fdef->def_obj->fn_args) {
        scope_args.push_back(arg->dtype);
    }
    m_scope.create_fn(fdef->def_obj->fn_name, scope_args);

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
        addr+=8;
    }

    // fdef
    m_asm += fdef->def_obj->fn_name+":\n";
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
    // TODO type-check against actual args from m_scope
    // eval args, create addresses
    for (auto &arg : fcall->fn_args) {
        gen_expr(arg);
    }
    // push args from their cur locations to the front
    for (int i=sz(fcall->fn_args)-1; i>=0; --i) {
        auto &arg = fcall->fn_args[i];
        int addr = addrof(arg);
        gen_stack_mov_raw(stkloc(addr), "%rax");
        int tmp;
        gen_stack_push("%rax", tmp);
    }

    // call function, store return address on stack
    m_asm += "\tcall "+fcall->fn_name+"\n";

    // [cleanup] args, which are dangling now. do it before pushing fcall result to stack
    // IMPORTANT: none of these ops should touch rax.
    m_scope.del_addr_top_n(sz(fcall->fn_args));
    for (auto &arg : fcall->fn_args) cleanup_dangling(arg);
    tighten_stack();
    // [/cleanup]

    gen_stack_push("%rax", fcall->_addr);
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    gen_stack_mov_raw(stkloc(addrof(ret->ret_val)), "%rax");
    m_asm += "\tmovq %rbp, %rsp\n"
             "\tpop %rbp\n"
             "\tret\n";
}

void Visitor::gen_val(uptr<Node> &val) {
    switch (val->dtype) {
    case DType::INT: gen_stack_push("$"+std::to_string(val->val_int), val->_addr); break;
    case DType::STR: throw std::runtime_error("[Visitor::gen_val] unimplemented"); break; // TODO
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
    } else {
        math=false;
    }

    if (math) {
        gen_stack_reserve(op->_addr);
        gen_expr(op->op_l);
        gen_expr(op->op_r);
        gen_stack_mov_raw(stkloc(addrof(op->op_l)), "%rax");
        gen_stack_mov_raw(stkloc(addrof(op->op_r)), "%rbx");
        // [cleanup] op_l and op_r are impossible to reference from here on out
        cleanup_dangling(op->op_l);
        cleanup_dangling(op->op_r);
        tighten_stack();
        // [/cleanup]
        m_asm += math_expr;

        string tg = "%rax";
        if (op->op_type == "%") tg = "%rdx";
        gen_stack_mov_raw(tg, stkloc(op->_addr));
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
        gen_stack_mov(addrof(op->op_r), m_scope.find_var(op->op_l->var_name));

        // [cleanup] op_r is useless now that op_l is the handle to op_r's value. op_l is VAR and doesn't need to be cleaned.
        cleanup_dangling(op->op_r);
        tighten_stack();
    } else if (op->op_l->type == NType::UNOP && op->op_l->unop_type == "*") {
        // eval dereferenced object, get loc of it
        gen_expr(op->op_l->unop_obj);
        gen_stack_mov_raw(stkloc(addrof(op->op_l->unop_obj)), "%rbx");
        gen_stack_mov_raw(stkloc(addrof(op->op_r)), "%rax");
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
        m_asm += "\tleaq "+stkloc(addrof(op->unop_obj))+", %rax\n";
        // [cleanup]
        cleanup_dangling(op->unop_obj);
        tighten_stack();
        // [/cleanup]
        gen_stack_push("%rax", op->_addr);
    } else if (op->unop_obj->type == NType::UNOP && op->unop_obj->unop_type == "*") {
        // LVALUE DEREF
        gen_expr(op->unop_obj->unop_obj);
        gen_stack_mov_raw(stkloc(addrof(op->unop_obj->unop_obj)), "%rax");
    }

    gen_stack_push("%rax", op->_addr);
}

void Visitor::gen_deref(uptr<Node> &op) {
    gen_expr(op->unop_obj);
    gen_stack_mov_raw(stkloc(addrof(op->unop_obj)), "%rax");
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
    gen_stack_mov_raw(stkloc(addrof(node->if_cond)), "%rax");
    // [cleanup] if_cond is dangling now
    cleanup_dangling(node->if_cond);
    tighten_stack();
    // [/cleanup]
    m_asm += "\ttest %rax, %rax\n"
             "\tjz "+else_label+"\n";

    // body
    int rsp=m_rsp;
    gen_expr(node->if_body);
    // [cleanup] if_body can technically be non-CPD (`if (x) 5;`) even if it does nothing, cleanup to be safe
    cleanup_dangling(node->if_body);
    tighten_stack();
    // [/cleanup]
    restore_rsp_scope(rsp);
    m_asm += "\tjmp "+end_label+"\n";

    // else
    m_asm += else_label+":\n";
    rsp=m_rsp;
    if (node->if_else) gen_expr(node->if_else);
    // [cleanup] same reasoning as if_body
    cleanup_dangling(node->if_else);
    tighten_stack();
    // [/cleanup]
    restore_rsp_scope(rsp);
    m_asm += end_label+":\n";
}

void Visitor::gen_while(uptr<Node> &node) {
    string start_label = ".L_start_"+std::to_string(node->while_id);
    string end_label = ".L_end_"+std::to_string(node->while_id);
    m_asm += start_label+":\n";

    // cond
    gen_expr(node->while_cond);
    gen_stack_mov_raw(stkloc(addrof(node->while_cond)), "%rax");
    // [cleanup] while_cond is dangling now
    cleanup_dangling(node->while_cond);
    tighten_stack();
    // [/cleanup]
    m_asm += "\ttest %rax, %rax\n"
             "\tjz "+end_label+"\n";

    // body
    int rsp=m_rsp;
    gen_expr(node->while_body);
    // [cleanup] same reasoning as gen_if
    cleanup_dangling(node->while_body);
    tighten_stack();
    // [/cleanup]
    restore_rsp_scope(rsp);
    m_asm += "\tjmp "+start_label+"\n";
    m_asm += end_label+":\n";
}

void Visitor::gen_stack_push(const string &val, int &addr) {
    m_rsp-=8;
    m_scope.claim_addr(m_rsp);
    m_asm += "\tpushq "+val+"\n";
    addr = m_rsp;
}

void Visitor::gen_stack_reserve(int &addr) {
    m_asm += "\tsubq $8, %rsp\n";
    m_rsp-=8;
    m_scope.claim_addr(m_rsp);
    addr = m_rsp;
}

void Visitor::gen_stack_pop(const string &dst) {
    m_scope.del_addr(m_rsp);
    m_rsp+=8;
    m_asm += "\tpopq "+dst+"\n";
}

void Visitor::gen_stack_mov(int src, int dst) {
    gen_stack_mov_raw(stkloc(src), "%rax");
    gen_stack_mov_raw("%rax", stkloc(dst));
}

void Visitor::gen_stack_mov_raw(const string &src, const string &dst) {
    m_asm += "\tmovq "+src+", "+dst+"\n";
}

void Visitor::restore_rsp_scope(int prev_rsp) {
    if (m_rsp != prev_rsp) {
        m_asm += "\t# restore_rsp_scope\n\taddq $"+std::to_string(prev_rsp-m_rsp)+", %rsp\n";
        m_rsp = prev_rsp;
    }
}

int Visitor::addrof(uptr<Node> &node) {
    switch (node->type) {
    case NType::FN: return node->_addr;
    case NType::VAL: return node->_addr;
    case NType::VAR: return m_scope.find_var(node->var_name);
    case NType::BINOP: return node->_addr;
    case NType::UNOP: return node->_addr;
    case NType::CPD:
    case NType::DEF:
    case NType::RET:
    case NType::IF:
    case NType::WHILE:
        break;
    }

    return -2;
}
