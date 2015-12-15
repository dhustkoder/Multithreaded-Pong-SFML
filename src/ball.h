#ifndef BALL_H
#define BALL_H
#include "shape.h"

constexpr float ballVelocity = 6.0F;
constexpr float ballRadius = 7.0F;

class Ball : public Shape
{
public:
	// give window size.
	Ball(const unsigned winWidth, const unsigned winHeight) noexcept;
	void treatCollisionWith(const Shape &collidedShape) noexcept;
	void update() noexcept override;
private:

	Ball(const Ball&) = delete;
	Ball(Ball&&) = delete;
	Ball& operator=(const Ball&) = delete;
	Ball& operator=(Ball&&) = delete;
};












#endif // BALL_H