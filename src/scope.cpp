#include "scope.h"
#include <stdexcept>
#include <cassert>

void Scope::push_layer() {
    m_layers.push_back(ScopeLayer{});
}

ScopeLayer Scope::pop_layer() {
    ScopeLayer res = std::move(m_layers.back());
    m_layers.pop_back();
    return res;
}

Addr Scope::find_var(const string &name) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        auto found = it->vdefs.find(name);
        if (found != it->vdefs.end()) {
            return found->second;
        }
    }

    throw std::runtime_error("[Scope::find_var] '"+name+"' not found\n");
}

DType Scope::find_var_dtype(const string &name) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        auto found = it->vdtypes.find(name);
        if (found != it->vdtypes.end()) {
            return found->second;
        }
    }

    throw std::runtime_error("[Scope::find_var] '"+name+"' not found\n");
}

const pair<DType,vec<DType>> &Scope::find_fn(const string &name) {
    return m_fdefs[name];
}

bool Scope::var_exists(const string &name) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        if (it->vdefs.find(name) != it->vdefs.end()) {
            return true;
        }
    }
    return false;
}

bool Scope::fn_exists(const string &name) {
    return m_fdefs.find(name) != end(m_fdefs);
}

void Scope::create_var(const string &name, Addr addr, DType dtype) {
    m_layers.back().vdefs[name] = addr;
    m_layers.back().vdtypes[name] = dtype;
}

void Scope::create_fn(const string &name, DType ret, vec<DType> args) {
    m_fdefs[name] = {ret,args};
}

void Scope::claim_stkaddr(int addr) {
    m_layers.back().stkaddrs.insert(addr);
}

void Scope::del_stkaddr(int addr) {
    auto it = m_layers.back().stkaddrs.find(addr);
    assert(it!=end(m_layers.back().stkaddrs));
    m_layers.back().stkaddrs.erase(it);
}

void Scope::del_stkaddr_top_n(int n) {
    for (int i=1; i<=n; ++i) {
        m_layers.back().stkaddrs.erase(begin(m_layers.back().stkaddrs));
    }
}

bool Scope::check_stkaddr(int addr) {
    bool ans=false;
    for (auto &l : m_layers) {
        ans|=l.stkaddrs.find(addr) != end(l.stkaddrs);
    }
    return ans;
}

int Scope::top_stkaddr() {
    int ans=0;
    for (auto &l : m_layers) {
        ans = std::min(ans,*begin(l.stkaddrs));
    }
    return ans;
}
