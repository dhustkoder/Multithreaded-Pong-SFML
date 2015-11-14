#ifndef PLAYER_H
#define PLAYER_H
#include "Paddle.h"





class Player : public Paddle
{
public:
	Player(float x, float y);

};


Player::Player(float x, float y) : Paddle(0,(y/2) - 40, 20, 80)
{

}









#endif