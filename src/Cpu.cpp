#include "pch.h"
#include "Cpu.h"

static sf::Vector2f calculateBallCollisionPosition(float x, float y, 
	const float velX, const float velY, const float leftLimit);



constexpr Seconds Cpu::defaultReactionDurationTime;
constexpr Seconds Cpu::defaultReactionDelayTime;

Cpu::Cpu(const Shape &ball) :
	Paddle(),
	m_ball(ball)
{

}



Cpu::Cpu(const float sizeX, const float sizeY, const Shape &ball)  
	: Paddle(sizeX, sizeY),
	m_ball(ball)
{

}



void Cpu::update() 
{
	
	const auto &ballVelocity = m_ball.getVelocity();

	if (ballVelocity.x > 0 && m_reactionDelay.finished())
	{
		if (!m_reactionDuration.isRunning()) // check if is first reaction
			m_reactionDuration.start();
		else if (m_reactionDuration.finished()) // reaction duration ends, start delay
			m_reactionDelay.start();
		

		const auto &ballPosition = m_ball.getPosition();
		const auto ballCollisionPosition =
			calculateBallCollisionPosition(ballPosition.x, ballPosition.y,
				ballVelocity.x, ballVelocity.y, this->getLeft());

		if (ballCollisionPosition.y < this->getTop()
			|| ballCollisionPosition.y > this->getBottom()) 
		{
			m_velocity->y = (ballCollisionPosition.y < this->getTop())
				? ((this->getTop() > 0) ? -defaultVelocity : 0)
				: ((this->getBottom() < GameWindow::Height) ? defaultVelocity : 0);

			m_shape->move(*m_velocity);
		}

	}

}


sf::Vector2f calculateBallCollisionPosition(float x, float y, 
	const float velX, const float velY, const float leftLimit)
{
	const auto absVelY = std::abs(velY);
	
	// ball is going Up
	if (velY < 0)
	{
		while (x < leftLimit && y > 0) {
			x += velX;
			y -= absVelY;
		}

		if (x < leftLimit && y <= 0) // ball hited the roof
			return calculateBallCollisionPosition(x, y, velX, -velY, leftLimit);
	}

	// ball is going Down
	else
	{
		while (x < leftLimit && y < GameWindow::Height) {
			x += velX;
			y += absVelY;
		}

		if (x < leftLimit && y >= GameWindow::Height) // ball hited the ground
			return calculateBallCollisionPosition(x, y, velX, -velY, leftLimit);
	}

	return { x, y };
}
