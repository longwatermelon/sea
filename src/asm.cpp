#include "asm.h"

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
        } else {
            throw std::runtime_error("[Visitor::gen_expr] def_obj wasn't FN");
        }
        break;
    }
    case NType::RET: gen_ret(expr); break;
    case NType::VAL: gen_stack_push(expr); break;

    case NType::VAR: break;
    case NType::FN: break;
    }
}

void Visitor::gen_cpd(uptr<Node> &cpd) {
    for (auto &node : cpd->cpd_nodes) {
        gen_expr(node);
    }
}

void Visitor::gen_fdef(uptr<Node> &fdef) {
    m_asm += fdef->def_obj->fn_name+":\n";
    m_asm += "\tpush %rbp\n"
             "\tmovq %rsp, %rbp\n";

    gen_expr(fdef->def_as);

    m_asm += "\tmovq %rbp, %rsp\n"
             "\tpop %rbp\n"
             "\tret\n";
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    m_asm += "\tmovq "+std::to_string(addrof(ret->ret_val))+"(%rsp), %rax\n";
}

void Visitor::gen_stack_push(uptr<Node> &node) {
    if (node->_addr != -1) return; // don't push if already existing

    switch (node->type) {
    case NType::VAL: {
        if (node->dtype == DType::INT) {
            m_asm += "\tsub $8, %rsp\n"
                     "\tmovq $"+std::to_string(node->val_int)+", "+std::to_string(m_rsp)+"(%rsp)\n";
            node->_addr = m_rsp;
            m_rsp+=8;
        } else {
            // TODO
            throw std::runtime_error("[Visitor::gen_stack_push] unimplemented VAL dtype");
        }
    } break;

    case NType::CPD:
    case NType::DEF:
    case NType::FN:
    case NType::RET:
    case NType::VAR:
        break;
    }
}

int Visitor::addrof(uptr<Node> &node) {
    switch (node->type) {
    case NType::CPD: return -2;
    case NType::DEF: return addrof(node->def_as);
    case NType::FN: return -2;
    case NType::RET: return -2;
    case NType::VAL: return node->_addr;
    // TODO scope class
    case NType::VAR: return -2;
    }
}
