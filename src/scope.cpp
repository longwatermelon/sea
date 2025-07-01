#include "scope.h"
#include <stdexcept>

void Scope::push_layer() {
    layers.push_back(ScopeLayer{});
}

void Scope::pop_layer() {
    if (!layers.empty()) {
        layers.pop_back();
    }
}

uptr<Node> &Scope::find_var(const string &name) {
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        auto found = it->vdefs.find(name);
        if (found != it->vdefs.end()) {
            return found->second;
        }
    }

    throw std::runtime_error("[Scope::find_var] '"+name+"' not found\n");
}

uptr<Node> &Scope::find_fn(const string &name) {
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        auto found = it->fdefs.find(name);
        if (found != it->fdefs.end()) {
            return found->second;
        }
    }

    throw std::runtime_error("[Scope::find_fn] '"+name+"' not found\n");
}

bool Scope::var_exists(const string &name) {
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        if (it->vdefs.find(name) != it->vdefs.end()) {
            return true;
        }
    }
    return false;
}

bool Scope::fn_exists(const string &name) {
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        if (it->fdefs.find(name) != it->fdefs.end()) {
            return true;
        }
    }
    return false;
}
