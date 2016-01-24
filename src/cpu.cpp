#include "pch.h"
#include "cpu.h"

static sf::Vector2f calculateBallCollisionPosition(float x, float y, 
	const float velX, const float velY, const float leftLimit) noexcept;



constexpr Seconds Cpu::defaultReactionDurationTime;
constexpr Seconds Cpu::defaultReactionDelayTime;

void Cpu::initialize() noexcept
{
	m_reactionDuration.setTime(defaultReactionDurationTime);
	m_reactionDelay.setTime(defaultReactionDelayTime);
	m_reactionDelay.start();
}

Cpu::Cpu(const Shape &ball) noexcept : 
	m_ball(ball)
{
	initialize();
}


Cpu::Cpu(const float sizeX, const float sizeY, const Shape &ball) noexcept : 
	Paddle(sizeX, sizeY),
	m_ball(ball)
{
	initialize();
}


#include <iostream>
void Cpu::update() noexcept
{
	
	const auto &ballVelocity = m_ball.getVelocity();

	if (ballVelocity.x > 0 && m_reactionDelay.finished())
	{
		if (!m_reactionDuration.isRunning()) {// check if is first reaction
			m_reactionDuration.start();
			std::cout << "cpu started reaction" << std::endl;
		}
		else if (m_reactionDuration.finished()) {// reaction duration ends, start delay
			m_reactionDelay.start();
			std::cout << "cpu stop reacting" << std::endl;
			return;
		}

		const auto &ballPosition = m_ball.getPosition();

		const auto ballCollisionPosition =
			calculateBallCollisionPosition(ballPosition.x, ballPosition.y,
				ballVelocity.x, ballVelocity.y, this->getLeft());

		if (ballCollisionPosition.y >= this->getTop()
			&& ballCollisionPosition.y <= this->getBottom()) 
		{
			return;
		}

		else
		{
			m_velocity->y = (ballCollisionPosition.y < this->getTop() ) 
				? ((this->getTop() > 0) ? -defaultVelocity : 0) 
				: ((this->getBottom() < GameWindow::Height ) ? defaultVelocity : 0);

			m_shape->move(*m_velocity);
		}

	}

	return;
}


sf::Vector2f calculateBallCollisionPosition(float x, float y, 
	const float velX, const float velY, const float leftLimit) noexcept
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
