#pragma once
#define sz(x) ((ll)size(x))
using ll=long long;
#include <vector>
#include <string>
#include <memory>
#include <map>
template <typename T> using vec=std::vector<T>;
using string=std::string;
template <typename T> using uptr=std::unique_ptr<T>;

template<typename T, typename... Args>
auto mkuq(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename U> using map=std::map<T,U>;
