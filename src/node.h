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

    // cpd
    vec<uptr<Node>> cpd_nodes;

    // int
    int int_val;

    // str
    string str_val;

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
};
