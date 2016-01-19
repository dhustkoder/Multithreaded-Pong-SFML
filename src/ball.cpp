#include "pch.h"
#include "ball.h"



Ball::Ball() noexcept : 
                                        // float(ballRadius) for clang/gcc, because make_unique take args by ref 
                                        // (it cant take ref to constexpr static member)
Shape({ ballRadius, ballRadius}, std::make_unique<sf::CircleShape>(float(ballRadius))),
		m_textureRect(0,0,64,64),
		m_clock(std::clock())
{
	m_velocity->y = m_velocity->x = ballVelocity;
	m_texture.loadFromFile("../Resources/balltexture");
	m_shape->setTexture(&m_texture);
	this->setPosition(Position::Middle);
	updateTextureDirectionFrame();

}

void Ball::treatCollision() noexcept
{

	float middle_of_collided_shape = (m_intersectingShape->getBottom() + m_intersectingShape->getTop()) * 0.5f;
	float middle_of_ball = ( getBottom() + getTop() ) * 0.5f;

	(middle_of_ball > middle_of_collided_shape) ? m_velocity->y = ballVelocity : m_velocity->y = -ballVelocity;
	
	m_velocity->x = (m_velocity->x == ballVelocity) ? -ballVelocity : ballVelocity;

	updateTextureDirectionFrame();
}


void Ball::update() noexcept
{
	if (getLeft() <= 0) {
		m_velocity->x = ballVelocity;
		updateTextureDirectionFrame();
	}
	else if (getRight() >= GameWindow::Width) {
		m_velocity->x = -ballVelocity;
		updateTextureDirectionFrame();
	}
	
	if (getTop() <= 0) {
		m_velocity->y = ballVelocity;
		updateTextureDirectionFrame();
	}
	else if (getBottom() >= GameWindow::Height) {
		m_velocity->y = -ballVelocity;
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
	if ((std::clock() - m_clock) > cexpr_div((clock_t)CLOCKS_PER_SEC, (clock_t)20))
	{
		++textureFrame;
		if (textureFrame > 7)
			textureFrame = 0;

		m_textureRect.left = ballTextureX * textureFrame;
		m_shape->setTextureRect(m_textureRect);

		m_clock = std::clock();
	}
}
