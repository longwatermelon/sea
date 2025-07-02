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

int Scope::find_var(const string &name) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        auto found = it->vdefs.find(name);
        if (found != it->vdefs.end()) {
            return found->second;
        }
    }

    throw std::runtime_error("[Scope::find_var] '"+name+"' not found\n");
}

int Scope::find_fn(const string &name) {
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        auto found = it->fdefs.find(name);
        if (found != it->fdefs.end()) {
            return found->second;
        }
    }

    throw std::runtime_error("[Scope::find_fn] '"+name+"' not found\n");
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
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        if (it->fdefs.find(name) != it->fdefs.end()) {
            return true;
        }
    }
    return false;
}

void Scope::create_var(const string &name, int addr, DType dtype) {
    m_layers.back().vdefs[name] = addr;
    m_layers.back().vdtypes[name] = dtype;
}

void Scope::claim_addr(int addr) {
    m_layers.back().addrs.insert(addr);
}

void Scope::del_addr(int addr) {
    auto it = m_layers.back().addrs.find(addr);
    assert(it!=end(m_layers.back().addrs));
    m_layers.back().addrs.erase(it);
}

void Scope::del_addr_top_n(int n) {
    for (int i=1; i<=n; ++i) {
        m_layers.back().addrs.erase(begin(m_layers.back().addrs));
    }
}

bool Scope::check_addr(int addr) {
    bool ans=false;
    for (auto &l : m_layers) {
        ans|=l.addrs.find(addr) != end(l.addrs);
    }
    return ans;
}
