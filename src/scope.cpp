#include "scope.h"
#include <stdexcept>

void Scope::push_layer() {
    m_layers.push_back(ScopeLayer{});
}

void Scope::pop_layer() {
    if (!m_layers.empty()) {
        m_layers.pop_back();
    }
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

void Scope::set_var(const string &name, int addr) {
    m_layers.back().vdefs[name] = addr;
}

void Scope::create_var(const string &name) {
    m_layers.back().vdefs[name] = -1;
}
