#pragma once
#include "util.h"
#include <stdexcept>

enum class NType {
    CPD, // compound
    VAL, // value
    FCALL, // function
    FDEF, // function def
    VAR, // variable
    TYPEVAR, // typed var (name:type)
    RET, // return
    BINOP, // binary operation
    IF, // if statement
    UNOP, // unary operator
    WHILE, // while loop
    STR, // string literal
    DTYPE, // dtype, needed for recognizing "int*" as an expression
    BREAK, // break
    CONT, // continue
};

enum class DTypeBase {
    INT,
    BYTE,
    VOID,
};

struct DType {
    DTypeBase base = DTypeBase::VOID;
    int ptrcnt=0;

    DType()=default;
    DType(DTypeBase base, int ptrcnt=0) : base(base), ptrcnt(ptrcnt) {}
};

inline bool is_dtypebase(const string &s) {
    return s == "int" || s == "void" || s == "byte";
}

inline DTypeBase str2dtypebase(const string &s) {
    if (s=="int") return DTypeBase::INT;
    else if (s=="byte") return DTypeBase::BYTE;
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
    case DTypeBase::BYTE: return 1;
    case DTypeBase::VOID: return 0;
    }
}

enum class AType {
    RBP,
    RIP,
    REG,
};

struct Addr {
    AType type=AType::RBP;
    int rbp_addr=-1;
    string rip_addr;
    string reg_name;

    Addr()=default;
    static Addr stack(int offset) { return Addr(AType::RBP, offset); }
    static Addr global(const string& name) { return Addr(AType::RIP, name); }
    static Addr reg(const string& name) { return Addr(AType::REG, name); }

    string repr(Arch arch) const {
        switch (type) {
        case AType::RBP: {
            switch (arch) {
            case Arch::x86_64: return std::to_string(rbp_addr)+"(%rbp)";
            case Arch::ARM64: return "[x29, #"+std::to_string(rbp_addr)+"]";
            }
        } break;
        case AType::RIP: {
            switch (arch) {
            case Arch::x86_64: return rip_addr+"(%rip)";
            case Arch::ARM64: return rip_addr;
            }
        } break;
        case AType::REG: return reg_name;
        }
    }
    bool exists() const {return type==AType::RBP ? rbp_addr!=-1 : sz(rip_addr)>0;}

    bool is_mem() const {
        switch (type) {
        case AType::RBP: return true;
        case AType::RIP: return true;
        case AType::REG: return reg_name[0]=='[' || reg_name.back()==')';
        }
    }

private:
    Addr(AType t, int offset) : type(t), rbp_addr(offset) {}
    Addr(AType t, const string& name) : type(t), rip_addr(t==AType::RIP ? name : ""), reg_name(t==AType::REG ? name : "") {}
};

struct Node {
    Node()=default;
    Node(NType type) : type(type) {}

    NType type;
    Addr _addr;

    // cpd
    vec<uptr<Node>> cpd_nodes;

    // val dtype
    DType val_dtype;

    // val: int (64-bit)
    ll val_int;

    // val: byte
    unsigned char val_byte;

    // fdef
    string fdef_name;
    vec<uptr<Node>> fdef_params; // typed vars
    uptr<Node> fdef_body;
    DType fdef_ret_dtype;

    // fcall
    string fcall_name;
    vec<uptr<Node>> fcall_args;

    // typevar
    string typevar_name;
    DType typevar_dtype;

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
