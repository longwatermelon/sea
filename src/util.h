#pragma once
#define sz(x) ((ll)size(x))
using ll=long long;
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <optional>
template <typename T> using vec=std::vector<T>;
using string=std::string;
template <typename T> using uptr=std::unique_ptr<T>;
template <typename T> using set=std::set<T>;
using std::end;
using std::begin;

template<typename T, typename... Args>
auto mkuq(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename U> using map=std::map<T,U>;

inline int precedence(const string &op) {
    static map<string,int> ans{
        {"=", 0},
        {"||", 1},
        {"&&", 1},
        {"==", 2},
        {"!=", 2},
        {"<", 3},
        {">", 3},
        {"<=", 3},
        {">=", 3},
        {"+", 4},
        {"-", 4},
        {"*", 5},
        {"/", 5},
        {"%", 5},
        {".", 6},
    };
    return ans[op];
}

enum class TType;
enum class NType;

string ttype2str(TType type);
string ntype2str(NType type);

enum class Arch {
    x86_64,
    ARM64,
};

std::optional<Arch> str2arch(const string &str);
