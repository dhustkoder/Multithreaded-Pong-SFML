#include "pch.h"
#include "cpu.h"

static sf::Vector2f calculateBallCollisionPosition(float x, float y, const float velX, const float velY, const float leftLimit);

void Cpu::initializer() noexcept
{
	m_reactionDurationClock = 0;
	m_reactionDelayClock = std::clock();
	this->setReactionDuration(defaultReactionDurationTime);
	this->setReactionDelay(defaultReactionDelayTime);
}


Cpu::Cpu(const Shape &ball) noexcept : 
	m_ball(ball)
{
	initializer();
}

Cpu::Cpu(const float sizeX, const float sizeY, const Shape &ball) noexcept : 
	Paddle(sizeX, sizeY),
	m_ball(ball)
{
	initializer();
}

void Cpu::setReactionDuration(const Seconds reactionDuration) noexcept
{
	m_reactionDurationTime = static_cast<Seconds>(CLOCKS_PER_SEC) * reactionDuration;
}

void Cpu::setReactionDelay(const Seconds reactionDelay) noexcept
{
	m_reactionDelayTime = static_cast<Seconds>(CLOCKS_PER_SEC) * reactionDelay;
}


void Cpu::update() noexcept
{
	
	const auto &ballVelocity = m_ball.getVelocity();
	ballVelocity == *m_velocity;
	if (ballVelocity.x > 0
		&& static_cast<Seconds>(std::clock() - m_reactionDelayClock) > m_reactionDelayTime)
	{
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
				? ((this->getTop() > 0) ? -defaultCpuVelocity : 0) 
				: ((this->getBottom() < GameWindow::Height ) ? defaultCpuVelocity : 0);

			m_shape->move(*m_velocity);
		}


		if (m_reactionDurationClock == 0) // check if is first reaction
			m_reactionDurationClock = std::clock();

		else if (static_cast<Seconds>(std::clock() - m_reactionDurationClock) > m_reactionDurationTime) {
			m_reactionDelayClock = std::clock();
			m_reactionDurationClock = 0;
		}
	}

	return;
}



static sf::Vector2f calculateBallCollisionPosition(float x, float y, const float velX, const float velY, const float leftLimit)
{
	const auto absVelY = std::abs(velY);
	
	// ball is going RightUp
	if (velY < 0)
	{
		while (x < leftLimit && y > 0) {
			x += velX;
			y -= absVelY;
		}

		if (x < leftLimit && y <= 0) // ball hited the roof
			return calculateBallCollisionPosition(x, y, velX, -velY, leftLimit);
	}

	// ball is going RightDown
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
