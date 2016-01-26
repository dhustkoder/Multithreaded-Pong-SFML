#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "Shape.h"
#include "Utility.h"


class Paddle : public Shape
{
	static constexpr float defaultWidth = 15;
	static constexpr float defaultHeight = 80;
public:

	Paddle() noexcept
	try : Shape({ cexpr_div(defaultWidth, 2.f), cexpr_div(defaultHeight, 2.f) },
			std::make_unique<sf::RectangleShape>(sf::Vector2f(defaultWidth, defaultHeight)))
	{
	}
	catch (std::bad_alloc& err) {
		printException(err, "Paddle::Paddle (default constructor)", true);
	}
	

	Paddle(const float sizeX, const float sizeY) noexcept
	try : Shape({ sizeX / 2.f, sizeY / 2.f },
			std::make_unique<sf::RectangleShape>(sf::Vector2f(sizeX, sizeY)))
	{
	}
	catch (std::bad_alloc& err) {
		printException(err, "Paddle::Paddle (default constructor)", true);
	}

	void treatCollision() override {};
	virtual bool isReady() = 0;
};





#endif // PADDLE_H
