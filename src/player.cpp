#include <SFML/Graphics/RectangleShape.hpp>
#include "player.h"
#include "gamewindow.h"
#include "utility.h"


Player::Player() noexcept : 
	Shape(defaultPaddleSize.getOrigin(), new sf::RectangleShape(defaultPaddleSize)),
	m_kUp(sf::Keyboard::Up), m_kDown(sf::Keyboard::Down)
{
	m_shape->setFillColor(sf::Color::White);
}


Player::Player(const float sizeX, const float sizeY) noexcept : 
	Shape({sizeX / 2.0f, sizeY / 2.0f}, new sf::RectangleShape({sizeX,sizeY})),
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



