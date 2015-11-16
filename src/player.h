#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include "paddle.h"

constexpr float playerWidth = 20.f;
constexpr float playerHeight = 80.f;
constexpr float playerVerticalCompensation = playerHeight / 2.f;
constexpr float playerHorizontalCompensation = playerWidth / 2.f;


class Player : public Paddle
{
public:
	// pass the window's resolution
	Player(const int winWidth, const int winHeight);
	void setKeys(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown);
	float getTop();
	float getBottom();
	float getRight();
	void update();
private:
	float  m_windowWidth, m_windowHeight;
	sf::Keyboard::Key m_kUp, m_kDown;


	Player(const Player&) = delete;
	Player(Player&&) = delete;


};




#endif