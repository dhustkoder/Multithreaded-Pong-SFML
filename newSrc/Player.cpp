#include "pch.h"
#include "Player.h"



Player::Player() : 
	m_kUp(sf::Keyboard::Up), 
	m_kDown(sf::Keyboard::Down)
{
	m_shape->setFillColor(sf::Color::White);
}


Player::Player(const float sizeX, const float sizeY) : 
	Paddle(sizeX, sizeY),
	m_kUp(sf::Keyboard::Up), 
	m_kDown(sf::Keyboard::Down)
{
	m_shape->setFillColor(sf::Color::White);

}



void Player::setKeys(const sf::Keyboard::Key keyUp, const sf::Keyboard::Key keyDown) noexcept
{
	m_kUp = keyUp;
	m_kDown = keyDown;
}



void Player::update()
{
	if (sf::Keyboard::isKeyPressed(m_kUp) && getTop() >= 0)
		m_velocity->y = -defaultVelocity;
	else if (sf::Keyboard::isKeyPressed(m_kDown) && getBottom() <= GameWindow::Height)
		m_velocity->y = defaultVelocity;	
	else
		m_velocity->y = 0;

	m_shape->move(*m_velocity);
}

bool Player::isReady() {
	return true;
}

