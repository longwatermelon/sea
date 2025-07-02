#pragma once
#include "util.h"
#include <stdexcept>

enum class NType {
    CPD, // compound
    VAL, // value
    DEF, // define
    FN, // function
    VAR, // variable
    RET, // return
    BINOP, // binary operation
    IF,
};

enum class DType {
    INT,
    STR,
    VOID,
};

inline bool is_dtype(const string &s) {
    return s=="int" || s=="str" || s=="void";
}

inline DType str2dtype(const string &s) {
    if (s=="int") return DType::INT;
    else if (s=="str") return DType::STR;
    else if (s=="void") return DType::VOID;
    else throw std::runtime_error("str2dtype failed");
    // TODO better error
}

struct Node {
    Node()=default;
    Node(NType type, DType dtype=DType::VOID) : type(type), dtype(dtype) {}

    NType type;
    DType dtype;
    int _addr=-1;

    // cpd
    vec<uptr<Node>> cpd_nodes;

    // val: int
    int val_int;

    // val: str
    string val_str;

    // def
    uptr<Node> def_obj;
    uptr<Node> def_as;

    // fn
    string fn_name;
    vec<uptr<Node>> fn_args;

    // var
    string var_name;

    // ret
    uptr<Node> ret_val;

    // binop
    uptr<Node> op_l, op_r;
    string op_type;

    // if
    uptr<Node> if_cond, if_body, if_else;
    int if_id;
};
