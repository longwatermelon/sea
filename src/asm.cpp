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
            m_scope.create_var(expr->def_obj->var_name, addr);
        } else if (expr->def_obj->type == NType::BINOP && expr->def_obj->op_type == "=") {
            int addr;
            gen_stack_reserve(addr);
            m_scope.create_var(expr->def_obj->op_l->var_name, addr);
            gen_expr(expr->def_obj);
        } else {
            throw std::runtime_error("[Visitor::gen_expr] def_obj wasn't FN or VAR or BINOP assignment");
        }
        break;
    }
    case NType::RET: gen_ret(expr); break;
    case NType::VAL: gen_val(expr); break;
    case NType::BINOP: gen_binop(expr); break;
    case NType::VAR: gen_var(expr); break;
    case NType::FN: gen_fcall(expr); break;
    case NType::IF: gen_if(expr); break;
    }

    cleanup_hanging_children(expr);
    tighten_stack();
}

void Visitor::cleanup_hanging_children(uptr<Node> &node) {
    auto cleanup = [&](uptr<Node> &x) {
        if (x && x->_addr != -1) {
            m_scope.del_addr(x->_addr);
            x->_addr = -1;
        }
    };

    switch (node->type) {
    case NType::BINOP: {
        cleanup(node->op_l);
        cleanup(node->op_r);
    } break; // already cleaned up
    case NType::CPD: {
        for (auto &x : node->cpd_nodes) {
            cleanup(x);
        }
    } break;
    case NType::DEF: {
        cleanup(node->def_as);
        cleanup(node->def_obj);
    } break;
    case NType::FN: {
        for (auto &x : node->fn_args) {
            cleanup(x);
        }
    } break;
    case NType::RET: {
        cleanup(node->ret_val);
    } break;
    case NType::VAL: break;
    case NType::VAR: break;
    case NType::IF: {
        // TODO this doesn't actually patch holes in the stack, need to clean up if_cond within function
        cleanup(node->if_cond);
        cleanup(node->if_body);
        cleanup(node->if_else);
    } break;
    }
}

void Visitor::tighten_stack() {
    int dif=0;
    while (m_rsp+dif<0 && !m_scope.check_addr(m_rsp+dif)) {
        dif+=8;
    }
    if (dif==0) return;

    m_rsp+=dif;
    m_asm += "\taddq $"+std::to_string(dif)+", %rsp\n";
}

void Visitor::gen_cpd(uptr<Node> &cpd) {
    m_scope.push_layer();
    int rsp = m_rsp;
    for (auto &node : cpd->cpd_nodes) {
        gen_expr(node);
    }
    restore_rsp_scope(rsp);
    m_scope.pop_layer();
}

void Visitor::gen_fdef(uptr<Node> &fdef) {
    // prep separate scope
    m_scope.push_layer();
    int prev_rsp = m_rsp;
    m_rsp=0;

    // prep params
    int addr=16;
    for (auto &param : fdef->def_obj->fn_args) {
        m_scope.create_var(param->def_obj->var_name, addr);
        addr+=8;
    }

    // fdef
    m_asm += fdef->def_obj->fn_name+":\n";
    m_asm += "\tpush %rbp\n"
             "\tmovq %rsp, %rbp\n\n";

    gen_expr(fdef->def_as);

    m_asm += "\n\tmovq %rbp, %rsp\n"
             "\tpop %rbp\n"
             "\tret\n\n";

    // restore og scope
    m_rsp = prev_rsp;
    m_scope.pop_layer();
}

void Visitor::gen_fcall(uptr<Node> &fcall) {
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

void Visitor::gen_var(uptr<Node> &var) {
    gen_stack_mov_raw(stkloc(m_scope.find_var(var->var_name)), "%rax");
    // TODO bake dtype into new VAL node for error typechecking later
    var = mkuq<Node>(NType::VAL);
    gen_stack_push("%rax", var->_addr);
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
    } else {
        math=false;
    }

    if (math) {
        gen_stack_reserve(op->_addr);
        gen_expr(op->op_l);
        gen_expr(op->op_r);
        gen_stack_mov_raw(stkloc(op->op_l->_addr), "%rax");
        gen_stack_mov_raw(stkloc(op->op_r->_addr), "%rbx");
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

    // move result to var in op_l
    assert(op->op_l->type == NType::VAR);
    assert(m_scope.var_exists(op->op_l->var_name));
    gen_stack_mov(op->op_r->_addr, m_scope.find_var(op->op_l->var_name));
}

void Visitor::gen_if(uptr<Node> &node) {
    string else_label = ".L_else_"+std::to_string(node->if_id);
    string end_label = ".L_end_"+std::to_string(node->if_id);

    // conditional
    gen_expr(node->if_cond);
    gen_stack_mov_raw(stkloc(addrof(node->if_cond)), "%rax");
    m_asm += "\ttest %rax, %rax\n"
             "\tjz "+else_label+"\n";

    // body
    int rsp=m_rsp;
    gen_expr(node->if_body);
    restore_rsp_scope(rsp);
    m_asm += "\tjmp "+end_label+"\n";

    // else
    m_asm += else_label+":\n";
    rsp=m_rsp;
    if (node->if_else) gen_expr(node->if_else);
    restore_rsp_scope(rsp);
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
        m_asm += "\taddq $"+std::to_string(prev_rsp-m_rsp)+", %rsp\n";
        m_rsp = prev_rsp;
    }
}

int Visitor::addrof(uptr<Node> &node) {
    switch (node->type) {
    case NType::FN: return node->_addr;
    case NType::VAL: return node->_addr;
    case NType::VAR: return m_scope.find_var(node->var_name);
    case NType::BINOP: return node->_addr;
    case NType::CPD:
    case NType::DEF:
    case NType::RET:
    case NType::IF:
        break;
    }

    return -2;
}
