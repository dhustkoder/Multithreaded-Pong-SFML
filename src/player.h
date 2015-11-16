#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include "paddle.h"


class Player : public Paddle
{
public:
	// pass the window's resolution
	Player(const int winWidth, const int winHeight);
	void setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown);
	void update();
private:
	float  m_windowWidth, m_windowHeight;
	sf::Keyboard::Key m_kUp, m_kDown;


	Player(const Player&) = delete;
	Player(Player&&) = delete;


};




#endif