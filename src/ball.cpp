#include "pch.h"
#include "ball.h"

static float genVelocity(const float min, const float max, const bool allowZero = false);
static float getPercent(const float value, const float percentage);
Ball::Ball() noexcept : 
                                        // float(defaultRadius) for clang/gcc, because make_unique take args by ref 
                                        // (it cant take ref to constexpr static member)
Shape({ defaultRadius, defaultRadius }, std::make_unique<sf::CircleShape>(float(defaultRadius))),
	m_textureRect(0, 0, defaultTextureWidth, defaultTextureHeight),
	m_clock(std::clock())
{
	m_velocity->y = m_velocity->x = defaultVelocity;
	m_texture.loadFromFile("../Resources/balltexture");
	m_shape->setTexture(&m_texture);
	this->setPosition(Position::Middle);
	updateTextureDirectionFrame();

	m_explosionTexture.loadFromFile("../Resources/explosion");
	m_explosionSprite.setTexture(m_explosionTexture);
	m_explosionSprite.setTextureRect({ 0,0,64,64 });
	m_explosionSprite.setOrigin(32, 32);

}




void Ball::treatCollision() noexcept
{
	updateIntersectingShape();
	if (m_intersectingShape == nullptr)
		return;

	m_velocity->x = (m_velocity->x > 0)
		? genVelocity(-defaultVelocity, -1.5f)
		: genVelocity(1.5f, defaultVelocity);


	float middle_of_collided_shape = 
		(m_intersectingShape->getBottom() + m_intersectingShape->getTop()) * 0.5f;

	float middle_of_ball = ( getBottom() + getTop() ) * 0.5f;

	(middle_of_ball > middle_of_collided_shape)
		? m_velocity->y = genVelocity(-defaultVelocity, defaultVelocity + 2.5f, true)
		: m_velocity->y = genVelocity(-defaultVelocity - 2.5f, defaultVelocity, true);
	
	updateTextureDirectionFrame();
}



void Ball::update() noexcept
{

	if (getLeft() <= 0) {
		m_velocity->x = genVelocity(1.5f, defaultVelocity);
		updateTextureDirectionFrame();
	}
	else if (getRight() >= GameWindow::Width) {
		m_velocity->x = genVelocity(-defaultVelocity, -1.5f);
		updateTextureDirectionFrame();
	}
	
	if (getTop() <= 0) {
		m_velocity->y = genVelocity(1.5f, defaultVelocity);
		updateTextureDirectionFrame();
	}
	else if (getBottom() >= GameWindow::Height) {
		m_velocity->y = genVelocity(-defaultVelocity, -1.5f);
		updateTextureDirectionFrame();
	}

	updateTextureAnimationFrame();
	m_shape->move(*m_velocity);

}
static bool drawingExplosion = false;
static sf::IntRect explosionRect(0, 0, 64, 64);
static std::clock_t explClock = 0;

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	
	
	target.draw(*m_shape, states);

	if (!drawingExplosion && this->isIntersecting()) {
		drawingExplosion = true;
		const_cast<sf::Sprite&>(m_explosionSprite).setPosition(this->getPosition());
	}
	
	if (drawingExplosion
		&& (std::clock() - explClock) > CLOCKS_PER_SEC / 60)
	{
		static int explLeft = 0;
		static int explTop = 0;

		target.draw(m_explosionSprite, states);
		
		++explLeft;
		if (explLeft > 3) 
		{
			++explTop;
			if (explTop > 3) {
				drawingExplosion = explosionRect.left = explosionRect.top = explLeft = explTop = explClock = 0;
				return;
			}
			explLeft = 0;
		}

		explosionRect.left = defaultTextureWidth * explLeft;
		explosionRect.top = defaultTextureHeight * explTop;
		const_cast<sf::Sprite&>(m_explosionSprite).setTextureRect(explosionRect);

		explClock = std::clock();
	}

}


void Ball::updateTextureDirectionFrame() noexcept
{
	const auto absVelX = std::abs(m_velocity->x);
	const auto absVelY = std::abs(m_velocity->y);

	if (m_velocity->x < 0 && absVelY < getPercent(absVelX, 30))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Left);
	
	else if (m_velocity->x < 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::UpLeft);

	else if (m_velocity->y < 0 && absVelX < getPercent(absVelY, 30))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Up);
	
	else if (m_velocity->x > 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::UpRight);
	
	else if (m_velocity->x > 0 && absVelY < getPercent(absVelX, 30))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Right);
	
	else if (m_velocity->x > 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::DownRight);
	
	else if (m_velocity->y > 0 && absVelX < getPercent(absVelY, 30))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Down);
	
	else if (m_velocity->x < 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::DownLeft);

	m_shape->setTextureRect(m_textureRect);

}

void Ball::updateTextureAnimationFrame() noexcept
{
	static int textureFrame = 0;
	const auto averageVel = 
		static_cast<std::clock_t>((std::abs(m_velocity->x) + std::abs(m_velocity->y)) / 2);

	if ((std::clock() - m_clock) > CLOCKS_PER_SEC / (averageVel + 20))
	{
		++textureFrame;
		if (textureFrame > 7)
			textureFrame = 0;

		m_textureRect.left = defaultTextureWidth * textureFrame;
		m_shape->setTextureRect(m_textureRect);

		m_clock = std::clock();
	}
}

#ifdef P_DEBUG
void Ball::debugControll() noexcept
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& getTop() > 0 && getLeft() > 0)
	{
		m_velocity->y = -defaultVelocity;
		m_velocity->x = -defaultVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& getTop() > 0 && getRight() < GameWindow::Width)
	{
		m_velocity->y = -defaultVelocity;
		m_velocity->x = defaultVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& getBottom() < GameWindow::Height && getLeft() > 0)
	{
		m_velocity->y = defaultVelocity;
		m_velocity->x = -defaultVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& getBottom() < GameWindow::Height
		&& getRight() < GameWindow::Width)
	{
		m_velocity->y = defaultVelocity;
		m_velocity->x = defaultVelocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& this->getTop() > 0)
		m_velocity->y = -defaultVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& this->getLeft() > 0)
		m_velocity->x = -defaultVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& this->getRight() < GameWindow::Width)
		m_velocity->x = defaultVelocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& this->getBottom() < GameWindow::Height)
		m_velocity->y = defaultVelocity;
	else {
		m_velocity->x = 0;
		m_velocity->y = 0;
	}
	m_shape->move(*m_velocity);
	
}
#endif


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

float getPercent(const float value, const float percentage)
{
	return (value / 100) * percentage;
}