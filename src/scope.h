#pragma once
#include "util.h"
#include "node.h"

struct ScopeLayer {
    map<string,Addr> vdefs;
    map<string,DType> vdtypes;
    set<int> stkaddrs;
};

class Scope {
public:
    Scope()=default;

    void push_layer();
    ScopeLayer pop_layer();

    bool var_exists(const string &name);
    bool fn_exists(const string &name);
    Addr find_var(const string &name);
    const vec<DType> &find_fn(const string &name);
    void create_var(const string &name, Addr addr, DType dtype);
    void create_fn(const string &name, vec<DType> args);

    void claim_stkaddr(int addr);
    void del_stkaddr(int addr);
    bool check_stkaddr(int addr);
    void del_stkaddr_top_n(int n);
    int top_stkaddr();

private:
    vec<ScopeLayer> m_layers;
    map<string, vec<DType>> m_fdefs;
};
