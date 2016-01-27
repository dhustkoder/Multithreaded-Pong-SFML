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

	Paddle() : 
		Shape(Type::Rectangle, {defaultWidth, defaultHeight}, { cexpr_div(defaultWidth, 2.f), cexpr_div(defaultHeight, 2.f) })
	{

	}
	

	Paddle(const float sizeX, const float sizeY) : 
		Shape(Type::Rectangle, { sizeX, sizeY }, { sizeX / 2.f, sizeY / 2.f })
	{

	}

	void treatCollision() override {};
	virtual bool isReady() = 0;
};





#endif // PADDLE_H
