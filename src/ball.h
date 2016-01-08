#ifndef BALL_H
#define BALL_H
#include "shape.h"

constexpr float ballVelocity = 1.5;
constexpr float ballRadius = 15.0;

class Ball final: public Shape
{
public:
	// uses window size informed for class Shape
	Ball() noexcept;
	void treatCollisionWith(const Shape &collidedShape) noexcept;
	void update() noexcept override;



};












#endif // BALL_H
