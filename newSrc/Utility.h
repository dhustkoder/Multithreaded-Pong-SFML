#ifndef UTILITY_H
#define UTILITY_H
#include <cstdio>
#include <type_traits>
#include <SFML/System/Vector2.hpp>

#define LOG(x, ...) printf(x "\n", ##__VA_ARGS__)
#define LOGerr(x, ...) fprintf(stderr, x "\n", ##__VA_ARGS__)
#define LOGread(x, ...) fscanf(stdin, x, ##__VA_ARGS__)
#define CONSOLE_PAUSE(x, ...) {LOG(x, ##__VA_ARGS__);LOG("Press To Continue..."); LOGread("%*c");}


constexpr void printException(const std::exception& exception,
	const char* const function, bool terminate = false)
{
	LOGerr("Exception caught in %s. Message: %s", 
		function, exception.what());
	if (terminate) {
		CONSOLE_PAUSE("the program will terminate");
		std::exit(0);
	}
}

constexpr void printException(const std::exception& exception,
	const char* const function, const char *const additionalMsg, bool terminate = false)
{
	LOGerr("Exception caught in %s. \nException Message: %s",
		function, exception.what());
	LOGerr("OBS: %s", additionalMsg);

	if (terminate) {
		CONSOLE_PAUSE("the program will terminate.");
		std::exit(0);
	}
}

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

#endif // UTILITY_H

