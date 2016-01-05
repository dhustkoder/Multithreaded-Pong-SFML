#ifndef UTILITY_H
#define UTILITY_H
#include <cstdio>
#include <SFML/System/Vector2.hpp>


template<typename T>
constexpr T cexpr_div(const T x, const T y)	{ return x / y; }
template<typename T>
constexpr T cexpr_sub(const T x, const T y)	{ return x - y; }

static constexpr struct DefaultPaddleSize
{
	constexpr static float x = 15;
	constexpr static float y = 80;
	sf::Vector2f operator /(const float div) const noexcept {
		return {x / div, y / div};
	}

	operator sf::Vector2f() const noexcept {
		return {x, y};
	}

}defaultPaddleSize{};


#define LOG(x, ...) printf(x "\n", ##__VA_ARGS__)
#define LOGerr(x, ...) fprintf(stderr, x "\n", ##__VA_ARGS__)










#endif // UTILITY_H

