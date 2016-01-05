#ifndef BALL_H
#define BALL_H
#include "shape.h"

constexpr auto ballVelocity = 5.5F;
constexpr auto ballRadius = 7.0F;

class Ball final: public Shape
{
public:
	// uses window size informed for class Shape
	Ball() noexcept;
	void treatCollisionWith(const Shape &collidedShape) noexcept;
	void update() noexcept override;



};












#endif // BALL_H
