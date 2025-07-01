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
    // TODO fix scope
    int prev_rsp = m_rsp;
    m_rsp=0;

    m_asm += fdef->def_obj->fn_name+":\n";
    m_asm += "\tpush %rbp\n"
             "\tmovq %rsp, %rbp\n\n";

    gen_expr(fdef->def_as);

    m_asm += "\n\tmovq %rbp, %rsp\n"
             "\tpop %rbp\n"
             "\tret\n\n";

    m_rsp = prev_rsp;
}

void Visitor::gen_fcall(uptr<Node> &fcall) {
    // TODO push args
    m_rsp+=8;
    m_asm += "\tcall "+fcall->fn_name+"\n"
             "\tsub $8, %rsp\n"
             "\tmovq %rax, -"+std::to_string(m_rsp)+"(%rbp)";
    fcall->_addr = m_rsp;
}

void Visitor::gen_ret(uptr<Node> &ret) {
    gen_expr(ret->ret_val);
    m_asm += "\tmovq -"+std::to_string(addrof(ret->ret_val))+"(%rbp), %rax\n";
}

void Visitor::gen_stack_push(uptr<Node> &node) {
    if (node->_addr != -1) return; // don't push if already existing

    switch (node->type) {
    case NType::VAL: {
        if (node->dtype == DType::INT) {
            m_rsp+=8;
            m_asm += "\tsub $8, %rsp\n"
                     "\tmovq $"+std::to_string(node->val_int)+", -"+std::to_string(m_rsp)+"(%rbp)\n";
            node->_addr = m_rsp;
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
    case NType::BINOP:
        break;
    }
}

int Visitor::addrof(uptr<Node> &node) {
    switch (node->type) {
    case NType::FN: return node->_addr;
    case NType::VAL: return node->_addr;
    case NType::VAR: return addrof(m_scope.find_var(node->var_name));
    case NType::CPD:
    case NType::DEF:
    case NType::RET:
    case NType::BINOP:
        return -2;
    }
}
