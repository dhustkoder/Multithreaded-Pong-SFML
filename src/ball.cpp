#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"
#include "gamewindow.h"
#include "utility.h"

Ball::Ball() noexcept : 
	Shape({cexpr_div(ballRadius, 2.f), cexpr_div(ballRadius, 2.f)},
	      std::make_unique<sf::CircleShape>(ballRadius))
{
	this->setPosition(Position::Middle);
	static sf::Image image;
	static sf::Texture texture;
	image.loadFromFile("../Resources/ballimg");
	texture.loadFromImage(image, sf::IntRect({(int)ballRadius / 2, (int)ballRadius / 2}, {597, 600}));
	m_shape->setTexture(&texture);

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
	if (getTop() <= 0)
		m_velocity->y = ballVelocity;
	else if(getBottom() >= GameWindow::Height)
		m_velocity->y = -ballVelocity;

	if(getLeft() <= 0)
		m_velocity->x = ballVelocity;
	else if(getRight() >= GameWindow::Width)
		m_velocity->x = -ballRadius;

	m_shape->rotate(m_velocity->y);
	m_shape->move(*m_velocity);
}

