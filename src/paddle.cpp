#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "paddle.h"


Paddle::Paddle(const float x, const float y, const float sizeX, const float sizeY) :
	m_shape(new sf::RectangleShape()), m_velocity(new sf::Vector2f())
{
	m_shape->setPosition(x, y);
	m_shape->setFillColor(sf::Color::White);
	m_shape->setSize({ sizeX, sizeY });
	m_shape->setOrigin({ sizeX / 2, sizeY / 2 });

}



const sf::Vector2f& Paddle::getPosition() const
{
	return m_shape->getPosition();
}




void Paddle::setPosition(const float x, const float y)
{
	m_shape->setPosition(x, y);
}



void Paddle::setVelocity(const float x, const float y)
{
	m_velocity->x = x;
	m_velocity->y = y;
}



const sf::Vector2f& Paddle::getVelocity() const
{
	return *m_velocity;
}


Paddle::operator sf::Drawable&()
{
	return *m_shape;
}
