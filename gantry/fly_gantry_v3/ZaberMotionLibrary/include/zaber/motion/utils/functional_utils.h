#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

namespace zml_util {

template <typename T, typename R>
std::vector<R> map_vec(const std::vector<T>& vec, std::function<R(const T&)> f) {
    std::vector<R> ret;
    std::transform(vec.cbegin(), vec.cend(), std::back_inserter(ret), f);
    return ret;
}

} // namespace util
