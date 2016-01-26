#include "pch.h"
#include "Ball.h"

static float genVelocity(const float min, const float max, const bool allowZero = false) noexcept;
static float getPercent(const float value, const float percentage) noexcept;



// static constexpr members definitions
// for linker, (only the static constexpr members which are
// used in a reference or pointer context must be defined here)
constexpr float Ball::defaultRadius;
constexpr const char* const Ball::defaultTextureFile;
constexpr const char* const Ball::defaultExplosionFile;


Ball::Ball() :
	Shape({ defaultRadius, defaultRadius }, std::make_unique<sf::CircleShape>(defaultRadius)),
	m_clock(std::clock()),
	m_textureRect(0, 0, defaultTextureWidth, defaultTextureHeight)
{
	if (!m_texture.loadFromFile(defaultTextureFile))
		throw FileNotFoundException(std::string("file not found: ") + defaultTextureFile);


	m_explosionEffect.loadSpriteSheet(defaultExplosionFile, { defaultTextureWidth, defaultTextureHeight },
	{ cexpr_mul(defaultTextureWidth, 3), cexpr_mul(defaultTextureHeight, 3) });
	

	m_velocity->y = m_velocity->x = defaultVelocity;
	m_shape->setTexture(&m_texture);
	this->setPosition(Position::Middle);
	updateTextureDirectionFrame();
}







void Ball::treatCollision()
{
	if (m_intersectingShape == nullptr)
		return;

	m_velocity->x = (m_velocity->x > 0)
		? genVelocity(-defaultVelocity, -1.5f)
		: genVelocity(1.5f, defaultVelocity);


	float middle_of_collided_shape = 
		(m_intersectingShape->getBottom() + m_intersectingShape->getTop()) * 0.5f;

	float middle_of_ball = ( getBottom() + getTop() ) * 0.5f;

	if (middle_of_ball > middle_of_collided_shape)
		m_velocity->y = genVelocity(-defaultVelocity, defaultVelocity + 2.5f, true);
	else 
		m_velocity->y = genVelocity(-defaultVelocity - 2.5f, defaultVelocity, true);
	
	updateTextureDirectionFrame();
	
	if (!m_explosionEffect.isActive()) {
		m_explosionEffect.setActive();
		m_explosionEffect.setPosition(this->getPosition());
	}
}



void Ball::update()
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
	m_explosionEffect.update();

}



void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*m_shape, states);
	if (m_explosionEffect.isActive())
		m_explosionEffect.draw(target, states);
}


void Ball::updateTextureDirectionFrame() noexcept
{
	const auto absVelX = std::abs(m_velocity->x);
	const auto absVelY = std::abs(m_velocity->y);

	if (m_velocity->x < 0 && absVelY < getPercent(absVelX, 45))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Left);
	
	else if (m_velocity->x < 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::UpLeft);

	else if (m_velocity->y < 0 && absVelX < getPercent(absVelY, 45))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Up);
	
	else if (m_velocity->x > 0 && m_velocity->y < 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::UpRight);
	
	else if (m_velocity->x > 0 && absVelY < getPercent(absVelX, 45))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Right);
	
	else if (m_velocity->x > 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::DownRight);
	
	else if (m_velocity->y > 0 && absVelX < getPercent(absVelY, 45))
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::Down);
	
	else if (m_velocity->x < 0 && m_velocity->y > 0)
		m_textureRect.top = cexpr_mul(defaultTextureHeight, BallTextureDirection::DownLeft);

	m_shape->setTextureRect(m_textureRect);

}

void Ball::updateTextureAnimationFrame() noexcept
{
	static int textureFrame = 0;
	const auto averageVel = 
		static_cast<std::clock_t>((std::abs(m_velocity->x) + std::abs(m_velocity->y)) / 2.f);

	if ((std::clock() - m_clock) > cexpr_div(CLOCKS_PER_SEC, (clock_t)20) * averageVel)
	{
		++textureFrame;
		if (textureFrame > 7)
			textureFrame = 0;

		m_textureRect.left = defaultTextureWidth * textureFrame;
		m_shape->setTextureRect(m_textureRect);

		m_clock = std::clock();
	}
}




float genVelocity(const float min, const float max, const bool allowZero) noexcept
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

float getPercent(const float value, const float percentage) noexcept
{
	return (value * 0.01f) * percentage;
}










/*
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
*/
