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

// aux constant object for default size and origin of paddle
constexpr struct DefaultPaddleSize
{
	constexpr static float x = 15;
	constexpr static float y = 80;
	sf::Vector2f getOrigin() const noexcept {
		return {cexpr_div(x,2.f), cexpr_div(y,2.f)};
	}
	
	operator sf::Vector2f() const noexcept {
		return {x, y};
	}

}defaultPaddleSize{};









#endif // UTILITY_H

