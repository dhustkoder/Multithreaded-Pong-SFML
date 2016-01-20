#include "pch.h"
#include "ball.h"

static float genVelocity(const float min, const float max, const bool allowZero = false);

Ball::Ball() noexcept : 
                                        // float(ballRadius) for clang/gcc, because make_unique take args by ref 
                                        // (it cant take ref to constexpr static member)
Shape({ ballRadius, ballRadius }, std::make_unique<sf::CircleShape>(float(ballRadius))),
	m_textureRect(0, 0, 64, 64),
	m_clock(std::clock()),
	m_debugControll(false)
{
	m_velocity->y = m_velocity->x = ballVelocity;
	m_texture.loadFromFile("../Resources/balltexture");
	m_shape->setTexture(&m_texture);
	this->setPosition(Position::Middle);
	updateTextureDirectionFrame();

}




void Ball::treatCollision() noexcept
{
	updateIntersectingShape();
	if (m_intersectingShape == nullptr)
		return;

	m_velocity->x = (m_velocity->x > 0)
		? genVelocity(-ballVelocity, -1.5f)
		: genVelocity(1.5f, ballVelocity);


	float middle_of_collided_shape = 
		(m_intersectingShape->getBottom() + m_intersectingShape->getTop()) * 0.5f;

	float middle_of_ball = ( getBottom() + getTop() ) * 0.5f;

	(middle_of_ball > middle_of_collided_shape)
		? m_velocity->y = genVelocity(-ballVelocity, ballVelocity + 2.5f, true)
		: m_velocity->y = genVelocity(-ballVelocity - 2.5f, ballVelocity, true);
	
	updateTextureDirectionFrame();
}



void Ball::update() noexcept
{
	if (m_debugControll)
		return debugControll();

	if (getLeft() <= 0) {
		m_velocity->x = genVelocity(1.5f, ballVelocity);
		updateTextureDirectionFrame();
	}
	else if (getRight() >= GameWindow::Width) {
		m_velocity->x = genVelocity(-ballVelocity, -1.5f);
		updateTextureDirectionFrame();
	}
	
	if (getTop() <= 0) {
		m_velocity->y = genVelocity(1.5f, ballVelocity);
		updateTextureDirectionFrame();
	}
	else if (getBottom() >= GameWindow::Height) {
		m_velocity->y = genVelocity(-ballVelocity, -1.5f);
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


void Ball::debugControll() noexcept
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& getTop() > 0 && getLeft() > 0)
	{
		m_velocity->y = -ballVelocity;
		m_velocity->x = -ballVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& getTop() > 0 && getRight() < GameWindow::Width)
	{
		m_velocity->y = -ballVelocity;
		m_velocity->x = ballVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& getBottom() < GameWindow::Height && getLeft() > 0)
	{
		m_velocity->y = ballVelocity;
		m_velocity->x = -ballVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& getBottom() < GameWindow::Height
		&& getRight() < GameWindow::Width)
	{
		m_velocity->y = ballVelocity;
		m_velocity->x = ballVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& this->getTop() > 0)
		m_velocity->y = -ballVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& this->getLeft() > 0)
		m_velocity->x = -ballVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& this->getRight() < GameWindow::Width)
		m_velocity->x = ballVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& this->getBottom() < GameWindow::Height)
		m_velocity->y = ballVelocity;
	else {
		m_velocity->x = 0;
		m_velocity->y = 0;
	}
	m_shape->move(*m_velocity);
	
}





static float genVelocity(const float min, const float max, const bool allowZero)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);
	const auto value = dist(gen);

	if (value != 0 || !allowZero)
		return value;
	else
		return genVelocity(min, max);

}