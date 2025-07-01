#pragma once
#include "node.h"

struct ScopeLayer {
    map<string,int> vdefs;
    map<string,int> fdefs;
};

class Scope {
public:
    Scope()=default;

    void push_layer();
    void pop_layer();
    const ScopeLayer& top() const {return m_layers.back();};

    bool var_exists(const string &name);
    bool fn_exists(const string &name);
    int find_var(const string &name);
    int find_fn(const string &name);
    void set_var(const string &name, int addr);
    void create_var(const string &name);

private:
    vec<ScopeLayer> m_layers;
};
