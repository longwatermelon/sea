#pragma once
#include "util.h"
#include <stdexcept>
#include <algorithm>

enum class DTypeBase {
    INT,
    BYTE,
    VOID,
    STRUCT,
};

struct DType {
    DTypeBase base = DTypeBase::VOID;
    string struct_name = "";
    int ptrcnt=0;

    DType()=default;
    DType(DTypeBase base, int ptrcnt=0) : base(base), ptrcnt(ptrcnt) {}
    DType(DTypeBase base, string struct_name, int ptrcnt=0) : base(base), struct_name(struct_name), ptrcnt(ptrcnt) {}
};

class Node;

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

class Visitor;

class Node {
public:
    virtual ~Node() = default;
    virtual void accept(Visitor &v) = 0;

    Addr _addr;
};

class CpdNode : public Node {
public:
    void accept(Visitor &v) override;

    vec<uptr<Node>> nodes;
};

class ValIntNode : public Node {
public:
    void accept(Visitor &v) override;

    ll value;
};

class ValByteNode : public Node {
public:
    void accept(Visitor &v) override;

    unsigned char value;
};

class TypevarNode : public Node {
public:
    void accept(Visitor &v) override;

    DType dtype;
    string name;
};

class FdefNode : public Node {
public:
    void accept(Visitor &v) override;

    string name;
    vec<uptr<TypevarNode>> params;
    uptr<Node> body;
    DType ret_dtype;
};

class FcallNode : public Node {
public:
    void accept(Visitor &v) override;

    string name;
    vec<uptr<Node>> args;
};

class VarNode : public Node {
public:
    void accept(Visitor &v) override;

    string name;
};

class RetNode : public Node {
public:
    void accept(Visitor &v) override;

    uptr<Node> expr;
};

class BinopNode : public Node {
public:
    void accept(Visitor &v) override;

    uptr<Node> l,r;
    string type;
};

class UnopNode : public Node {
public:
    void accept(Visitor &v) override;

    uptr<Node> obj;
    string type;
};

class IfNode : public Node {
public:
    void accept(Visitor &v) override;

    uptr<Node> cond;
    uptr<Node> body, else_;
    int id;
};

class WhileNode : public Node {
public:
    void accept(Visitor &v) override;

    uptr<Node> cond;
    uptr<Node> body;
    int id;
};

class ForNode : public Node {
public:
    void accept(Visitor &v) override;

    uptr<Node> init, cond, upd;
    uptr<Node> body;
    int id;
};

class DtypeNode : public Node {
public:
    void accept(Visitor &v) override;

    DType dtype;
};

class SdefNode : public Node {
public:
    void accept(Visitor &v) override;

    string name;
    vec<uptr<TypevarNode>> membs;
};

class BreakNode : public Node {
public:
    void accept(Visitor &v) override;
};

class ContinueNode : public Node {
public:
    void accept(Visitor &v) override;
};

bool is_dtypebase(const string &s, vec<SdefNode*> &sdefs);
DTypeBase str2dtypebase(const string &s, vec<SdefNode*> &sdefs);
int find_struct_size(DType type, vec<SdefNode*> &sdefs);
int dtype_size(DType type, vec<SdefNode*> &sdefs);
int find_struct_size(DType type, vec<SdefNode*> &sdefs);
int find_member_offset(DType type, string name, vec<SdefNode*> &sdefs);
