#include "shape.h"


Shape::Shape(const float originX, const float originY, sf::Shape *shapeType) :
	m_shape(shapeType), m_velocity(new sf::Vector2f()),
	m_horizontalCompensation(originX), m_verticalCompensation(originY)
{
	m_shape->setOrigin(originX, originY);
	m_velocity->x = 0;
	m_velocity->y = 0;
}


sf::Shape *const Shape::getShape()
{
	return m_shape.get();
}


sf::Vector2f *const Shape::getVelocity()
{
	return m_velocity.get();
}



float Shape::getRight() const
{
	return m_shape->getPosition().x + m_horizontalCompensation;
}

float Shape::getLeft() const
{
	return m_shape->getPosition().x - m_horizontalCompensation;
}



float Shape::getTop() const
{
	return m_shape->getPosition().y - m_verticalCompensation;
}

float Shape::getBottom() const
{
	return m_shape->getPosition().y + m_verticalCompensation;
}

void Shape::setCompensation(const float h, const float v)
{
	m_horizontalCompensation = h;
	m_verticalCompensation = v;
}

void Shape::setPosition(const float x, const float y)
{
	m_shape->setPosition(x, y);
}

