#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"
#include "utility.h"

Ball::Ball() noexcept : 
	Shape({cexpr_div(ballRadius, 2.f), cexpr_div(ballRadius, 2.f)}, new sf::CircleShape(ballRadius))	
{
	m_shape->setFillColor(sf::Color::Red);
    this->setPosition(Position::Middle);
	m_velocity->y = m_velocity->x = ballVelocity;

}

void Ball::treatCollisionWith(const Shape &collidedShape) noexcept
{

	float middle_of_collided_shape = (collidedShape.getBottom() + collidedShape.getTop()) / 2.0F;
	float middle_of_ball = ( getBottom() + getTop() ) / 2.0F;

	(middle_of_ball > middle_of_collided_shape) ? m_velocity->y = ballVelocity : m_velocity->y = -ballVelocity;
	
	m_velocity->x = (m_velocity->x == ballVelocity) ? -ballVelocity : ballVelocity;
	
}

void Ball::update() noexcept
{
	if (getTop() < 1)
		m_velocity->y = ballVelocity;
	else if(getBottom() > m_windowHeight)
		m_velocity->y = -ballVelocity;

	if(getLeft() < 1)
		m_velocity->x = ballVelocity;
	else if(getRight() > m_windowWidth)
		m_velocity->x = -ballRadius;

	m_shape->move(*m_velocity);
}

