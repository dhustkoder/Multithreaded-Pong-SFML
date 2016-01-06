#include "player.h"
#include "gamewindow.h"
#include "utility.h"


Player::Player() noexcept : 
	m_kUp(sf::Keyboard::Up), m_kDown(sf::Keyboard::Down)
{
	m_shape->setFillColor(sf::Color::White);
}


Player::Player(const float sizeX, const float sizeY) noexcept : 
	Paddle(sizeX, sizeY),
	m_kUp(sf::Keyboard::Up), m_kDown(sf::Keyboard::Down)
{
	m_shape->setFillColor(sf::Color::White);
}

void Player::setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown)
{
	m_kUp = keyUp;
	m_kDown = keyDown;
}




void Player::update() noexcept
{
	if (sf::Keyboard::isKeyPressed(m_kUp) && getTop() >= 0)
		m_velocity->y = -playerVelocity;
	else if (sf::Keyboard::isKeyPressed(m_kDown) && getBottom() <= GameWindow::height)
		m_velocity->y = playerVelocity;	
	else
		m_velocity->y = 0;
	
	m_shape->move(*m_velocity);
}

bool Player::isReady() noexcept {
	return true;
}

