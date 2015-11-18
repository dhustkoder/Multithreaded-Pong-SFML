#include <SFML/Graphics/RectangleShape.hpp>
#include "player.h"



Player::Player(const float winX, const float winY, const float sizeX, const float sizeY) : 
	Shape(sizeX / 2.0F, sizeY / 2.0F, new sf::RectangleShape({sizeX,sizeY})),
	m_windowWidth(winX), m_windowHeight(winY), m_kUp(sf::Keyboard::Up), m_kDown(sf::Keyboard::Down)
{

	m_shape->setFillColor(sf::Color::White);
	m_shape->setPosition(0, winY / 2.0F);

}

void Player::setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown)
{
	m_kUp = keyUp;
	m_kDown = keyDown;
}




void Player::update()
{
	if (sf::Keyboard::isKeyPressed(m_kUp) && getTop() > 0)
		m_velocity->y = -playerVelocity;

	else if (sf::Keyboard::isKeyPressed(m_kDown) && getBottom() < m_windowHeight)
		m_velocity->y = playerVelocity;

	else
		m_velocity->y = 0;

	m_shape->move(*m_velocity);
}



