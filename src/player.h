#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include "shape.h"

constexpr float playerVelocity = 4.0F;

class Player : public Shape
{
public:
	// pass the window's resolution, and player size
	Player(const float winWidth, const float winHeight, const float sizeX, const float sizeY);
	void setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown);
	void update();
private:
	float  m_windowWidth, m_windowHeight;
	sf::Keyboard::Key m_kUp, m_kDown;

	Player(const Player&) = delete;
	Player(Player&&) = delete;


};




#endif