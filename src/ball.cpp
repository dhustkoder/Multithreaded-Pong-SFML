#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"
#include "gamewindow.h"
#include "particlesystem/particle.h"
#include "utility.h"


Ball::Ball() noexcept : 
	Shape({ballRadius,ballRadius}, std::make_unique<sf::CircleShape>(float(ballRadius))), // float(ballRadius) for clang/gcc
		                                                                                  // because make_unique take args by ref (it cant take ref to constexpr static member)
		m_textureRect(0,0,64,64),
		m_clock(std::clock())
{
	m_velocity->y = m_velocity->x = ballVelocity;
	m_texture.loadFromFile("../Resources/balltexture");
	m_shape->setTexture(&m_texture);
	this->setPosition(Position::Middle);
	updateTextureDirectionFrame();

}

void Ball::treatCollisionWith(const Shape &collidedShape) noexcept
{

	float middle_of_collided_shape = (collidedShape.getBottom() + collidedShape.getTop()) / 2.0F;
	float middle_of_ball = ( getBottom() + getTop() ) / 2.0F;

	(middle_of_ball > middle_of_collided_shape) ? m_velocity->y = ballVelocity : m_velocity->y = -ballVelocity;
	
	m_velocity->x = (m_velocity->x == ballVelocity) ? -ballVelocity : ballVelocity;

	updateTextureDirectionFrame();
}


void Ball::update() noexcept
{
	
	if (getTop() <= 0) {
		m_velocity->y = ballVelocity;
		updateTextureDirectionFrame();
	}
	else if (getBottom() >= GameWindow::Height) {
		m_velocity->y = -ballVelocity;
		updateTextureDirectionFrame();
	}

	if (getLeft() <= 0) {
		m_velocity->x = ballVelocity;
		updateTextureDirectionFrame();
	}
	else if (getRight() >= GameWindow::Width) {
		m_velocity->x = -ballVelocity;
		updateTextureDirectionFrame();
	}

	updateTextureAnimationFrame();
	m_shape->move(*m_velocity);

}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*m_shape, states);
}


void Ball::updateTextureDirectionFrame() noexcept
{
	if (m_velocity->x < 0 && m_velocity->y == 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::Left);
	else if (m_velocity->x < 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::UpLeft);
	else if (m_velocity->x == 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::Up);
	else if (m_velocity->x > 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::UpRight);
	else if (m_velocity->x > 0 && m_velocity->y == 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::Right);
	else if (m_velocity->x > 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::DownRight);
	else if (m_velocity->x == 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::Down);
	else if (m_velocity->x < 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(ballTextureY, BallTextureDirection::DownLeft);

	m_shape->setTextureRect(m_textureRect);

}

void Ball::updateTextureAnimationFrame() noexcept
{
	static int textureFrame = 0;
	if ((std::clock() - m_clock) > cexpr_div(CLOCKS_PER_SEC, (clock_t)60))
	{
		++textureFrame;
		if (textureFrame > 7)
			textureFrame = 0;

		m_textureRect.left = ballTextureX * textureFrame;
		m_shape->setTextureRect(m_textureRect);

		m_clock = std::clock();
	}
}