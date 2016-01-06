#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "shape.h"
#include "utility.h"


class Paddle : public Shape
{
	constexpr static float defaultWidth = 15;
	constexpr static float defaultHeight = 80;
public:
	Paddle() noexcept;
	Paddle(const float sizeX, const float sizeY) noexcept;
	virtual bool isReady() = 0;

};

inline
Paddle::Paddle() noexcept :
	Shape({cexpr_div(defaultWidth, 2.f), cexpr_div(defaultWidth, 2.f)},
	      std::make_unique<sf::RectangleShape>(sf::Vector2f(defaultWidth, defaultHeight)).release())
{

}

inline
Paddle::Paddle(const float sizeX, const float sizeY) noexcept :
	Shape({sizeX / 2.f, sizeY / 2.f},
	      std::make_unique<sf::RectangleShape>(sf::Vector2f(sizeX, sizeY)).release())
{

}


#endif // PADDLE_H
