#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "player.h"

Player::Player(const float x, const float y) : Paddle(0, (y / 2), playerWidth, playerHeight),
	m_windowWidth(x), m_windowHeight(y)
{


}

inline float Player::getTop()
{
	return getPosition().y - (playerVerticalCompensation);
}

inline float Player::getBottom()
{
	return getPosition().y + (playerVerticalCompensation);
}


void Player::update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && getTop() > 0)
		setVelocity(0, -paddleVelocity);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && getBottom() < m_windowHeight)
		setVelocity(0, paddleVelocity);

	else
		setVelocity(0, 0);

	m_shape->move(*m_velocity);
}



