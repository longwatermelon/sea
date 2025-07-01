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
    }
}

void Visitor::gen_cpd(uptr<Node> &cpd) {
    m_scope.push_layer();
    for (auto &node : cpd->cpd_nodes) {
        gen_expr(node);
    }
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
        m_asm += "\tmovq "+stkloc(addr)+", %rax\n";
        int tmp;
        gen_stack_push("%rax", tmp);
    }

    // call function, store return address on stack
    m_asm += "\tcall "+fcall->fn_name+"\n";
    gen_stack_push("%rax", fcall->_addr);
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    m_asm += "\tmovq "+stkloc(addrof(ret->ret_val))+", %rax\n";
}

void Visitor::gen_val(uptr<Node> &val) {
    switch (val->dtype) {
    case DType::INT: gen_stack_push("$"+std::to_string(val->val_int), val->_addr); break;
    case DType::STR: throw std::runtime_error("[Visitor::gen_val] unimplemented"); break; // TODO
    case DType::VOID: throw std::runtime_error("[Visitor::gen_val] unreachable void"); break;
    }
}

void Visitor::gen_var(uptr<Node> &var) {
    m_asm += "\tmovq "+stkloc(m_scope.find_var(var->var_name))+", %rax\n";
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
        gen_expr(op->op_l);
        gen_expr(op->op_r);
        gen_stack_pop("%rbx");
        gen_stack_pop("%rax");
        m_asm += math_expr;

        string tg = "%rax";
        if (op->op_type == "%") tg = "%rdx";
        gen_stack_push(tg, op->_addr);
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

void Visitor::gen_stack_push(const string &val, int &addr) {
    if (addr != -1) return;

    m_rsp-=8;
    m_asm += "\tpushq "+val+"\n";
    addr = m_rsp;
}

void Visitor::gen_stack_reserve(int &addr) {
    m_asm += "\tsubq $8, %rsp\n";
    m_rsp-=8;
    addr = m_rsp;
}

void Visitor::gen_stack_pop(const string &dst) {
    m_rsp+=8;
    m_asm += "\tpopq "+dst+"\n";
}

void Visitor::gen_stack_mov(int src, int dst) {
    m_asm += "\tmovq "+stkloc(src)+", %rax\n"
             "\tmovq %rax, "+stkloc(dst)+"\n";
}

int Visitor::addrof(uptr<Node> &node) {
    switch (node->type) {
    case NType::FN: return node->_addr;
    case NType::VAL: return node->_addr;
    case NType::VAR: return m_scope.find_var(node->var_name);
    case NType::BINOP: return node->_addr;
    case NType::CPD:
    case NType::DEF:
    case NType::RET: break;
    }

    return -2;
}
