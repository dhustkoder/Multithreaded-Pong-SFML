#include "pch.h"
#include "cpu.h"


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

void Cpu::setReactionDuration(seconds reactionTime)
{
	m_reactionDurationTime = static_cast<seconds>(CLOCKS_PER_SEC) * reactionTime;
}

void Cpu::setReactionDelay(seconds reactionDelay)
{
	m_reactionDelayTime = static_cast<seconds>(CLOCKS_PER_SEC) * reactionDelay;
}

void Cpu::initializer()
{
	m_reactionDurationClock = 0;
	m_reactionDelayClock = std::clock();
	this->setReactionDuration(defaultReactionDurationTime);
	this->setReactionDelay(defaultReactionDelayTime);
}

void Cpu::update() noexcept
{
	if ( m_ball.getVelocity().x > 0
		&& static_cast<seconds>(std::clock() - m_reactionDelayClock) > m_reactionDelayTime)
	{
		const auto &ballVelocity = m_ball.getVelocity();
		const auto &ballPosition = m_ball.getPosition();
		const auto &cpuPosition = m_shape->getPosition();
		auto cpuLeft = GameWindow::Width - this->getLeft();

		if (ballVelocity.y > 0 && ballPosition.y < cpuPosition.y)
		{
			auto ballPosY = ballPosition.y;
			auto ballPosX = ballPosition.x;
			
			while ( ballPosY < GameWindow::Height
				&& ballPosX < cpuLeft)
			{
				ballPosY += ballVelocity.y;
				ballPosX += ballVelocity.x / 2.f;
			}

			if(ballPosY >= GameWindow::Height
				&& ballPosX < cpuLeft)
				while (ballPosY > 0
					&& ballPosX < cpuLeft)
				{
					ballPosY -= ballVelocity.y;
					ballPosX += ballVelocity.x / 2.f;
				}

			
			if (ballPosY >= this->getTop()
				&& ballPosY <= this->getBottom())
			{
				return;
			}
		}

		else if (ballVelocity.y < 0 && ballPosition.y > cpuPosition.y)
		{
			auto ballPosY = ballPosition.y;
			auto ballPosX = ballPosition.x;
			while ( ballPosY > 0
				&& ballPosX < cpuLeft)
			{
				ballPosY -= ballVelocity.y;
				ballPosX += ballVelocity.x / 2.f;
			}

			if (ballPosY <= 0
				&& ballPosX < cpuLeft)
				while (ballPosY < GameWindow::Height
					&& ballPosX < cpuLeft)
				{
					ballPosY += ballVelocity.y;
					ballPosX += ballVelocity.x / 2.f;
				}
			

			if (ballPosY >= this->getTop()
				&& ballPosY <= this->getBottom())
			{
				return;
			}
		}

		else
		{
			m_velocity->y = (ballVelocity.y > 0) ? 
				((this->getBottom() < GameWindow::Height) ? defaultCpuVelocity : 0) 
				: 
				((this->getTop() > 0) ? -defaultCpuVelocity : 0);

			m_shape->move(*m_velocity);
		}


		if(m_reactionDurationClock == 0)// check if is first reaction
			m_reactionDurationClock = std::clock();

		else if (static_cast<seconds>(std::clock() - m_reactionDurationClock) > m_reactionDurationTime) {
			m_reactionDelayClock = std::clock();
			m_reactionDurationClock = 0;
		}
	}

	
}
