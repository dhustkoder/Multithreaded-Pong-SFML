#include "shape.h"

Shape::Shape(const unsigned winWidth, const unsigned winHeight, 
const float originX, const float originY, sf::Shape *shape) noexcept :

	m_shape(shape), m_velocity(new sf::Vector2f()),
	m_horizontalCompensation(originX), m_verticalCompensation(originY),
	m_windowWidth(winWidth), m_windowHeight(winHeight)
{
	m_shape->setOrigin(originX, originY);
	m_velocity->x = 0;
	m_velocity->y = 0;
}



const sf::Vector2f &Shape::getVelocity() const noexcept
{
	return *m_velocity;
}

void Shape::setCompensation(const float h, const float v) noexcept
{
	m_horizontalCompensation = h;
	m_verticalCompensation = v;
}

void Shape::setPosition(const float x, const float y) noexcept
{
	m_shape->setPosition(x, y);
}


