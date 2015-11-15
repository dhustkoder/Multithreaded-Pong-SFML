#ifndef PLAYER_H
#define PLAYER_H
#include "paddle.h"

constexpr float playerWidth = 20.f;
constexpr float playerHeight = 80.f;
constexpr float playerVerticalCompensation = playerHeight / 2.f;
constexpr float playerHorizontalCompensation = playerWidth / 2.f;
class Player : public Paddle
{
public:
	// pass the window's resolution
	Player(const float winWidth, const float winHeight);
	float getTop();
	float getBottom();
	float getRight();
	void update();
private:
	float  m_windowWidth, m_windowHeight;



};




#endif