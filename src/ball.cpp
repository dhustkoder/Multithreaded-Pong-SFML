#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"

Ball::Ball(const float winWidth, const float winHeight) : 
	Shape(ballRadius / 2.0F, ballRadius / 2.0F, new sf::CircleShape(ballRadius)),
	 m_maxBottom(winHeight), m_maxRight(winWidth)
{
	this->getShape()->setFillColor(sf::Color::Red);
	this->getShape()->setPosition(winWidth / 2.0F, winHeight / 2.0F);

	this->getVelocity()->x = ballVelocity;
	this->getVelocity()->y = ballVelocity;

}

void Ball::update()
{
	static sf::Vector2f *velocity = this->getVelocity();
	static sf::Shape *shape = this->getShape();

	if(getTop() < 1)
		velocity->y = ballVelocity;
	else if(getBottom() > m_maxBottom)
		velocity->y = -ballVelocity;

	if(getLeft() < 1)
		velocity->x = ballVelocity;
	else if(getRight() > m_maxRight)
		velocity->x = -ballVelocity;

	shape->move(*velocity);
}

