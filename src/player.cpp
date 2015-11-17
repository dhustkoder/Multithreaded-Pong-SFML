#include <SFML/Graphics/RectangleShape.hpp>
#include "player.h"



Player::Player(const float winX, const float winY, const float sizeX, const float sizeY) : 
	Shape(sizeX / 2.0F, sizeY / 2.0F, new sf::RectangleShape({sizeX,sizeY})),
	m_windowWidth(winX), m_windowHeight(winY), m_kUp(sf::Keyboard::Up), m_kDown(sf::Keyboard::Down)
{

	this->getShape()->setFillColor(sf::Color::White);
	this->getShape()->setPosition(0, winY / 2.0F);

}

void Player::setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown)
{
	m_kUp = keyUp;
	m_kDown = keyDown;
}




void Player::update()
{
	sf::Vector2f *velocity = this->getVelocity();

	if (sf::Keyboard::isKeyPressed(m_kUp) && getTop() > 0)
		velocity->y = -playerVelocity;

	else if (sf::Keyboard::isKeyPressed(m_kDown) && getBottom() < m_windowHeight)
		velocity->y = playerVelocity;

	else
		velocity->y = 0;

	this->getShape()->move(*velocity);
}



