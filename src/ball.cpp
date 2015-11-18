#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"

Ball::Ball(const float winWidth, const float winHeight) : 
	Shape(ballRadius / 2.0F, ballRadius / 2.0F, new sf::CircleShape(ballRadius)),
	 m_maxBottom(winHeight), m_maxRight(winWidth)
{
	m_shape->setFillColor(sf::Color::Red);
	m_shape->setPosition(winWidth / 2.0F, winHeight / 2.0F);

	m_velocity->x = ballVelocity;
	m_velocity->y = ballVelocity;

}

void Ball::treatCollision(const Shape &collidedShape)
{
	float middle_of_collided_shape = collidedShape.getTop() + (collidedShape.getBottom() / 2.0F);
	float middle_of_ball = getTop() + (getBottom() / 2.0F);

	if (middle_of_ball > middle_of_collided_shape)
		m_velocity->y = ballVelocity;
	else
		m_velocity->y = -ballVelocity;

	m_velocity->x = (m_velocity->x == ballVelocity) ? -ballVelocity : ballVelocity;
	
}

void Ball::update()
{
	if(getTop() < 1)
		m_velocity->y = ballVelocity;
	else if(getBottom() > m_maxBottom)
		m_velocity->y = -ballVelocity;

	if(getLeft() < 1)
		m_velocity->x = ballVelocity;
	else if(getRight() > m_maxRight)
		m_velocity->x = -ballVelocity;

	m_shape->move(*m_velocity);
}

