
#include "player.h"



Player::Player(const float winX, const float winY, const float sizeX, const float sizeY) : Paddle(0, (y / 2), sizeX, sizeY),
	m_windowWidth(winX), m_windowHeight(winY), m_kUp(sf::Keyboard::Up), m_kDown(sf::Keyboard::Down)
{


}

void Player::setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown)
{
	m_kUp = keyUp;
	m_kDown = keyDown;
}




void Player::update()
{
	if (sf::Keyboard::isKeyPressed(m_kUp) && getTop() > 0)
		setVelocity(0, -paddleVelocity);

	else if (sf::Keyboard::isKeyPressed(m_kDown) && getBottom() < m_windowHeight)
		setVelocity(0, paddleVelocity);

	else
		setVelocity(0, 0);

	m_shape->move(*m_velocity);
}



