#ifndef MY_MATH_H
#define MY_MATH_H

#include <algorithm>
#include <array>

template <size_t n>
std::array<double, n> M_x(std::array<std::array<double, n>, n> M, std::array<double, n> x) {
    std::array<double, n> res;
    for (size_t j = 0; j < n; ++j) {
        res[j] = 0;
        for (size_t i = 0; i < n; ++i) {
            res[j] += M[j][i]*x[i];
        }
    }

    return res;
}

#endif // MY_MATH_H