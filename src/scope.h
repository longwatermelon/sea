#pragma once
#include "node.h"

struct ScopeLayer {
    map<string,uptr<Node>> vdefs;
    map<string,uptr<Node>> fdefs;
};

class Scope {
public:
    Scope()=default;

    void push_layer();
    void pop_layer();
    const ScopeLayer& top() const {return layers.back();};

    bool var_exists(const string &name);
    bool fn_exists(const string &name);
    uptr<Node> &find_var(const string &name);
    uptr<Node> &find_fn(const string &name);

private:
    vec<ScopeLayer> layers;
};
