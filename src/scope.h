#pragma once
#include "util.h"
#include "node.h"

struct ScopeLayer {
    map<string,int> vdefs;
    map<string,int> fdefs;
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
    int find_fn(const string &name);
    void create_var(const string &name, int addr);
    void claim_addr(int addr);
    void del_addr(int addr);
    bool check_addr(int addr);

private:
    vec<ScopeLayer> m_layers;
};
