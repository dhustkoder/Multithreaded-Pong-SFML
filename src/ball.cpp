#include "ball.h"

Ball::Ball(const float x, const float y, const float radius) : 
	m_shape(new sf::CircleShape()), m_velocity(new sf::Vector2f)
{
	m_shape->setPosition(x, y);
	m_shape->setRadius(radius);
	m_shape->setFillColor(sf::Color::Red);
}

const sf::Vector2f & Ball::getPosition() const
{
	// TODO: insert return statement here
	return m_shape->getPosition();
}

const sf::Vector2f & Ball::getVelocity() const
{
	// TODO: insert return statement here
	return *m_velocity;
}

void Ball::setPosition(const float x, const float y)
{

}

void Ball::setVelocity(const float x, const float y)
{

}
void Ball::update()
{

}

Ball::operator sf::Drawable&()
{
	return *m_shape;
}
