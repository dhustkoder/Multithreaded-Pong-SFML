#ifndef UTILITY_H
#define UTILITY_H
#include <cstdio>
#include <SFML/System/Vector2.hpp>


#define LOG(x, ...) printf(x "\n", ##__VA_ARGS__)
#define LOGerr(x, ...) fprintf(stderr, x "\n", ##__VA_ARGS__)




template<typename T>
constexpr T cexpr_div(const T x, const T y)	{ return x / y; }
template<typename T>
constexpr T cexpr_sub(const T x, const T y)	{ return x - y; }
template<typename T>
constexpr T cexpr_mult(const T x, const T y) { return x * y; }










#endif // UTILITY_H

