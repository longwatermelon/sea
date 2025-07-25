#pragma once
#include "util.h"
#include "node.h"
using std::pair;

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
    DType find_var_dtype(const string &name);
    const pair<DType,vec<DType>> &find_fn(const string &name);
    void create_var(const string &name, Addr addr, DType dtype);
    void create_fn(const string &name, DType ret, vec<DType> args);

    void claim_stkaddr(int addr);
    void del_stkaddr(int addr);
    bool check_stkaddr(int addr);
    void del_stkaddr_top_n(int n);
    int top_stkaddr();
    int layer_count() const {return sz(m_layers);};

private:
    vec<ScopeLayer> m_layers;
    map<string, pair<DType,vec<DType>>> m_fdefs;
};
