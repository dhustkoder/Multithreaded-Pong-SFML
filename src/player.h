#ifndef PLAYER_H
#define PLAYER_H
#include "Paddle.h"
constexpr float playerWidth = 20.f;
constexpr float playerHeight = 80.f;
constexpr float playerVerticalCompensation = playerHeight / 2.f;

class Player : public Paddle
{
public:
	// pass the window's resolution
	Player(const float winWidth, const float winHeight);
	float getTop();
	float getBottom();
	void update();
private:
	float  m_windowWidth, m_windowHeight;



};




#endif