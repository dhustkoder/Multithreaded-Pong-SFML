#ifndef UTILITY_H
#define UTILITY_H
#include <cstdio>
#include <type_traits>
#include <SFML/System/Vector2.hpp>
#include "sfe.h"
#define LOG(x, ...) printf(x "\n", ##__VA_ARGS__)
#define LOGerr(x, ...) fprintf(stderr, x "\n", ##__VA_ARGS__)
#define LOGread(x, ...) fscanf(stdin, x, ##__VA_ARGS__)
#define CONSOLE_PAUSE(x, ...) {LOG(x, ##__VA_ARGS__);LOG("Press To Continue..."); LOGread("%*c");}
SFE_NAMESPACE
namespace utility {


// enumerators to underlying-type
template<typename E>
constexpr std::underlying_type_t<E> toUType(E enumerator) noexcept
{
	return static_cast<std::underlying_type_t<E>>(enumerator);
}

// compile-time calculations
template<typename T>
constexpr T cexpr_add(const T x, const T y) noexcept { return x + y; }
template<typename T>
constexpr T cexpr_sub(const T x, const T y) noexcept { return x - y; }
template<typename T>
constexpr T cexpr_div(const T x, const T y) noexcept { return x / y; }
template<typename T>
constexpr T cexpr_mul(const T x, const T y) noexcept { return x * y; }

// compile-time calculations
// specializations for second argument as scoped enumerator
template<typename T, typename T2>
constexpr std::enable_if_t<std::is_enum<T2>::value, T>
cexpr_add(const T x, const T2 y) noexcept 
{ 
	return x + toUType(y); 
}

template<typename T, typename T2>
constexpr std::enable_if_t<std::is_enum<T2>::value, T>
cexpr_sub(const T x, const T2 y) noexcept 
{ 
	return x - toUType(y); 
}

template<typename T, typename T2>
constexpr std::enable_if_t<std::is_enum<T2>::value, T>
cexpr_div(const T x, const T2 y) noexcept 
{ 
	return x / toUType(y); 
}

template<typename T, typename T2>
constexpr std::enable_if_t<std::is_enum<T2>::value, T>
cexpr_mul(const T x, const T2 y) noexcept 
{
	return x * toUType(y); 
}





// type_traits
template<class T, class ...Ts>
struct is_one_of;

//specializations
template<class T, class... Ts>
struct is_one_of<T, T, Ts...> : std::true_type {}; // the same type is right ahead , true_type then.

template<class T, class T2, class ...Ts>
struct is_one_of<T, T2, Ts...> : is_one_of<T, Ts...>{}; // the same type is not right ahead?
													    // then discard it and call the next
template<class T>
struct is_one_of<T> : std::false_type {}; // no one match... false_type then.



}
NAMESPACE_END
#endif // UTILITY_H

