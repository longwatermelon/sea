#pragma once
#include "util.h"
#include "node.h"

struct ScopeLayer {
    map<string,int> vdefs;
    map<string,DType> vdtypes;
    set<int> addrs;
};

class Scope {
public:
    Scope()=default;

    void push_layer();
    ScopeLayer pop_layer();

    bool var_exists(const string &name);
    bool fn_exists(const string &name);
    int find_var(const string &name);
    const vec<DType> &find_fn(const string &name);
    void create_var(const string &name, int addr, DType dtype);
    void create_fn(const string &name, vec<DType> args);

    void claim_addr(int addr);
    void del_addr(int addr);
    bool check_addr(int addr);
    void del_addr_top_n(int n);

private:
    vec<ScopeLayer> m_layers;
    map<string, vec<DType>> m_fdefs;
};
