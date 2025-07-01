#pragma once
#define sz(x) ((ll)size(x))
using ll=long long;
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
template <typename T> using vec=std::vector<T>;
using string=std::string;
template <typename T> using uptr=std::unique_ptr<T>;
template <typename T> using set=std::set<T>;

template<typename T, typename... Args>
auto mkuq(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename U> using map=std::map<T,U>;

inline int precedence(const string &op) {
    static map<string,int> ans{
        {"=", 0},
        {"||", 1},
        {"==", 2},
        {"+", 3},
        {"-", 3},
        {"*", 4},
        {"/", 4},
    };
    return ans[op];
}

inline string stkloc(int addr) {
    return std::to_string(addr)+"(%rbp)";
}
