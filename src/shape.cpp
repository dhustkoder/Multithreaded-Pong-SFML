#include "shape.h"


Shape::Shape(const float originX, const float originY, sf::Shape *shapeType) :
	m_shape(shapeType), m_velocity(new sf::Vector2f()),
	m_horizontalCompensation(originX), m_verticalCompensation(originY)
{
	m_shape->setOrigin(originX, originY);
	m_velocity->x = 0;
	m_velocity->y = 0;
}


inline float Shape::getRight() const
{
	return m_shape->getPosition().x + m_horizontalCompensation;
}

inline float Shape::getLeft() const
{
	return m_shape->getPosition().x - m_horizontalCompensation;
}



inline float Shape::getTop() const
{
	return m_shape->getPosition().y - m_verticalCompensation;
}

inline float Shape::getBottom() const
{
	return m_shape->getPosition().y + m_verticalCompensation;
}

const sf::Vector2f &Shape::getVelocity() const
{
	return *m_velocity;
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

bool Shape::isColliding(const Shape &first, const Shape &second) 
{
	return  first.getBottom() >= second.getTop() && first.getTop() <= second.getBottom()
		&& first.getLeft() <= second.getRight() && first.getRight() >= second.getLeft();

}

