#include "pch.h"
#include "Ball.h"

static float genVelocity(const float min, const float max, const bool allowZero = false);
static float getPercent(const float value, const float percentage);



// static constexpr members definitions
// for linker, (only the static constexpr members which are
// used in a reference or pointer context must be defined here)
constexpr float Ball::defaultRadius;
constexpr const char* const Ball::defaultTextureFile;
constexpr const char* const Ball::defaultExplosionFile;


Ball::Ball() :
	Shape(Type::Circle, defaultRadius, { defaultRadius, defaultRadius }),
	m_sprite(defaultTextureFile, {64,64}, {64 * 7, 64 * 7}, *m_velocity)
{
	m_sprite.setUpdateDirectionFunction(&updateDirectionFunction);
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
	
}



void Ball::update()
{

	if (getLeft() <= 0) {
		m_velocity->x = genVelocity(1.5f, defaultVelocity);
		m_sprite.updateDirection();
	}
	else if (getRight() >= GameWindow::Width) {
		m_velocity->x = genVelocity(-defaultVelocity, -1.5f);
		m_sprite.updateDirection();
	}
	
	if (getTop() <= 0) {
		m_velocity->y = genVelocity(1.5f, defaultVelocity);
		m_sprite.updateDirection();
	}
	else if (getBottom() >= GameWindow::Height) {
		m_velocity->y = genVelocity(-defaultVelocity, -1.5f);
		m_sprite.updateDirection();
	}

	m_shape->move(*m_velocity);
	m_sprite.updateAnimationFrame();
	
}



void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(*m_shape, states);
}


void Ball::updateDirectionFunction(SpriteAnimation& sprite, const sf::Vector2f& velocity)
{
	enum Direction { Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft };
	const auto absVelX = std::abs(velocity.x);
	const auto absVelY = std::abs(velocity.y);

	if (velocity.x < 0 && absVelY < getPercent(absVelX, 45))
		sprite.setDirection(Left);

	else if (velocity.x < 0 && velocity.y < 0)
		sprite.setDirection(UpLeft);

	else if (velocity.y < 0 && absVelX < getPercent(absVelY, 45))
		sprite.setDirection(Up);

	else if (velocity.x > 0 && velocity.y < 0)
		sprite.setDirection(UpRight);

	else if (velocity.x > 0 && absVelY < getPercent(absVelX, 45))
		sprite.setDirection(Right);

	else if (velocity.x > 0 && velocity.y > 0)
		sprite.setDirection(DownRight);

	else if (velocity.y > 0 && absVelX < getPercent(absVelY, 45))
		sprite.setDirection(Down);

	else if (velocity.x < 0 && velocity.y > 0)
		sprite.setDirection(DownLeft);

}





float genVelocity(const float min, const float max, const bool allowZero)
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
