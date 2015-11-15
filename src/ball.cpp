#include "ball.h"

Ball::Ball(const float x, const float y) : 
	m_shape(new sf::CircleShape()), m_velocity(new sf::Vector2f(4.0F,4.0F))
{
	m_shape->setPosition(x, y);
	m_shape->setRadius(ballRadius);
	m_shape->setOrigin(ballHorizontalCompensation,ballVerticalCompensation);
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

void Ball::genVelocity()
{
	m_velocity->x = 4.2F;
	m_velocity->y = 4.2F;
}


inline float Ball::getTop()
{
	return m_shape->getPosition().y - ballVerticalCompensation;
}

inline float Ball::getBottom()
{
	return m_shape->getPosition().y + ballVerticalCompensation;
}

inline float Ball::getLeft()
{
	return m_shape->getPosition().x - ballHorizontalCompensation;
}

inline float Ball::getRight()
{
	return m_shape->getPosition().x + ballHorizontalCompensation;
}

void Ball::update()
{
	if(getTop() < 1)
		m_velocity->y = 4.2F;
	else if(getBottom() > 420)
		m_velocity->y = -4.2F;

	if(getLeft() < 1)
		m_velocity->x = 4.2F;
	else if(getRight() > 800)
		m_velocity->x = -4.2F;

	m_shape->move(*m_velocity);
}

Ball::operator sf::Drawable&()
{
	return *m_shape;
}
