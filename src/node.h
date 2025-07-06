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
    IF, // if statement
    UNOP, // unary operator
    WHILE, // while loop
    STR, // string literal
    DTYPE, // dtype, needed for recognizing "int*" as an expression
};

enum class DTypeBase {
    INT,
    VOID,
};

struct DType {
    DTypeBase base = DTypeBase::VOID;
    int ptrcnt=0;

    DType()=default;
    DType(DTypeBase base, int ptrcnt=0) : base(base), ptrcnt(ptrcnt) {}
};

inline bool is_dtypebase(const string &s) {
    return s=="int" || s=="void";
}

inline DTypeBase str2dtypebase(const string &s) {
    if (s=="int") return DTypeBase::INT;
    else if (s=="void") return DTypeBase::VOID;
    else throw std::runtime_error("str2dtype failed");
    // TODO better error
}

inline int dtype_size(DType type) {
    if (type.ptrcnt>0) {
        return 8;
    }

    switch (type.base) {
    case DTypeBase::INT: return 8;
    case DTypeBase::VOID: return 0;
    }
}

enum class AType {
    RBP,
    RIP,
};

struct Addr {
    AType type=AType::RBP;
    int rbp_addr=-1;
    string rip_addr;

    Addr()=default;
    Addr(int rbp_offset) : type(AType::RBP), rbp_addr(rbp_offset) {}
    Addr(const string &rip_name) : type(AType::RIP), rip_addr(rip_name) {}

    string repr() const {return type==AType::RBP ? stkloc(rbp_addr) : rip_addr+"(%rip)";}
    bool exists() const {return type==AType::RBP ? rbp_addr!=-1 : sz(rip_addr)>0;}
};

struct Node {
    Node()=default;
    Node(NType type, DType dtype=DType()) : type(type), dtype(dtype) {}

    NType type;
    DType dtype;
    Addr _addr;

    // cpd
    vec<uptr<Node>> cpd_nodes;

    // val: int
    int val_int;

    // def
    uptr<Node> def_obj;

    // fn
    string fn_name;
    vec<uptr<Node>> fn_args;
    uptr<Node> fn_body;

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

    // unop
    uptr<Node> unop_obj;
    string unop_type;

    // while
    uptr<Node> while_cond, while_body;
    int while_id;

    // string
    string str_val;
    int str_id;

    // dtype
    DType dtype_type;
};
