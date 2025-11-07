#include "node.h"
#include "asm.h"

void CpdNode::accept(Visitor &v) { v.visit(this); }
void ValIntNode::accept(Visitor &v) { v.visit(this); }
void ValByteNode::accept(Visitor &v) { v.visit(this); }
void TypevarNode::accept(Visitor &v) { v.visit(this); }
void FdefNode::accept(Visitor &v) { v.visit(this); }
void FcallNode::accept(Visitor &v) { v.visit(this); }
void VarNode::accept(Visitor &v) { v.visit(this); }
void RetNode::accept(Visitor &v) { v.visit(this); }
void BinopNode::accept(Visitor &v) { v.visit(this); }
void UnopNode::accept(Visitor &v) { v.visit(this); }
void IfNode::accept(Visitor &v) { v.visit(this); }
void WhileNode::accept(Visitor &v) { v.visit(this); }
void DtypeNode::accept(Visitor &v) { v.visit(this); }
void SdefNode::accept(Visitor &v) { v.visit(this); }
void BreakNode::accept(Visitor &v) { v.visit(this); }
void ContinueNode::accept(Visitor &v) { v.visit(this); }

int find_struct_size(DType type, vec<SdefNode*> &sdefs) {
    for (auto &sdef : sdefs) {
        if (sdef->name == type.struct_name) {
            int ans = 0;
            for (uptr<TypevarNode> &typevar : sdef->membs) {
                ans += dtype_size(typevar->dtype, sdefs);
            }
            return ans;
        }
    }

    throw std::runtime_error("[node.h find_struct_size] unreachable - requested dtype doesn't exist as a struct definition in sdefs");
}

int find_member_offset(DType type, string name, vec<SdefNode*> &sdefs) {
    for (auto &sdef : sdefs) {
        if (sdef->name == type.struct_name) {
            int offset = 0;
            for (int i = 0; i < sz(sdef->membs); ++i) {
                if (sdef->membs[i]->name == name) {
                    return offset;
                }

                offset += dtype_size(sdef->membs[i]->dtype, sdefs);
            }
        }
    }

    throw std::runtime_error("[node.h find_member_offset] unreachable - requested dtype doesn't exist as a struct definition in sdefs");
}

bool is_dtypebase(const string &s, vec<SdefNode*> &sdefs) {
    return s == "int" || s == "void" || s == "byte" || std::find_if(begin(sdefs), end(sdefs), [&](SdefNode *sdef){return sdef->name == s;}) != end(sdefs);
}

DTypeBase str2dtypebase(const string &s, vec<SdefNode*> &sdefs) {
    if (s=="int") return DTypeBase::INT;
    else if (s=="byte") return DTypeBase::BYTE;
    else if (s=="void") return DTypeBase::VOID;
    else if (std::find_if(begin(sdefs), end(sdefs), [&](SdefNode *sdef){return sdef->name == s;}) != end(sdefs)) return DTypeBase::STRUCT;
    else throw std::runtime_error("str2dtype failed");
    // TODO better error
}

int dtype_size(DType type, vec<SdefNode*> &sdefs) {
    if (type.ptrcnt>0) {
        return 8;
    }

    switch (type.base) {
    case DTypeBase::INT: return 8;
    case DTypeBase::BYTE: return 1;
    case DTypeBase::VOID: return 0;
    case DTypeBase::STRUCT: return find_struct_size(type, sdefs);
    }
}
